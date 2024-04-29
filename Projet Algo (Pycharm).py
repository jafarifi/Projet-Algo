import tkinter as tk
from tkinter import Canvas
import paho.mqtt.client as mqtt
import json

root = tk.Tk()
root.title("Traqueur d'animaux")

canvas = Canvas(root, width=800, height=600, bg='white')
canvas.pack()


def dessiner_point(position, nom, couleur="red"):
    x, y = position

    if not (-200 <= x <= 200 and -200 <= y <= 200):
        couleur = "blue"

    x += 400
    y = 400 - y
    canvas.create_oval(x - 10, y - 10, x + 10, y + 10, fill=couleur)
    canvas.create_text(x, y - 15, text=nom, font=("Arial", 12), fill=couleur)


def on_message_callback(client_inst, userdata, message):
    try:

        valeur = message.payload.decode("utf-8")
        print(f"Topic: {message.topic} Message: {valeur}")
        valeur_json = json.loads(valeur)
        valeur_lora = valeur_json["object"]["message"]
        liste = valeur_lora.split(":")
        nom = liste[0]
        position = (int(liste[1]), int(liste[2]))
        dessiner_point(position, nom)
    except Exception as e:
        print("Erreur lors de la lecture du message JSON:", e)


client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, "vgi")

client.connect("srv-lora.isep.fr", 1883, 60)

client.on_message = on_message_callback

client.subscribe("#")

client.loop_start()

root.mainloop()