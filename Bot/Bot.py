import telebot
from telebot import types
import requests
from handler import handler


with open('token.txt', 'r', encoding='utf8') as f:
    token = f.read()
    bot = telebot.TeleBot(token)



@bot.message_handler(commands=['start'])
def start(mes, res=False):
    bot.send_message(mes.from_user.id, 'Привет!!!')

    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    butt_datInf = types.KeyboardButton('Получить данные') 
    markup.add(butt_datInf)
    bot.send_message(mes.from_user.id, 'Нажмите "Получить данные", чтобы получить данные с датчиков.', reply_markup=markup)


@bot.message_handler(content_types=['text'])    
def text_handle(m):
    if m.text.strip() == 'Получить данные':
        try:
            response = requests.get('http://192.168.1.69:5000/api')
            response.encoding = 'utf-8'
            mas = handler(response.text)

            bot.send_message(m.from_user.id, f'Контроллер №{mas[-1]}:\n Температура равна: {mas[0]}\n Влажность равна: {mas[1]}\n \
Влажность почвы: {mas[2]}\n Уровень воды в баке: {mas[3]}\n Угол наклона форточки: {mas[-2]}')
  
        except:
            bot.send_message(m.from_user.id, 'Сервер не отвечает!')
    else:
        bot.send_message(m.from_user.id, f'Команда "{m.text}" не известна.')




bot.polling(none_stop=True, interval=0)