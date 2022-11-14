# Hackeando um monitor de pressão arterial com o ESP32

Este projeto faz parte do desenvolvimento de um [Sistema de Baixo Custo para Monitoramento Remoto de Sinais Vitais](https://github.com/Andreick/ESP32-health-monitor).

O método de obtenção das medições é o mesmo utilizado na série de vídeos [ARDUINO BLOOD PRESSURE REVERSE ENGINEERING](https://www.youtube.com/playlist?list=PLwEgGe9BgSDUJ5pvvxOqygIP3YL5-haQK), que consiste em interceptar os dados salvos em uma EEPROM.

A explicação a seguir assume que o leitor conhece o protocolo I2C, recomendo a leitura do artigo [Understanding the I2C Bus](https://www.ti.com/lit/an/slva704/slva704.pdf).

## O aparelho de pressão arterial

O medidor utilizado é o LP200 Premium.

<p align="center"><img src="https://raw.githubusercontent.com/Andreick/blood-pressure-monitor-hack/assets/imgs/LP200.jpg" alt="Aparelho de pressão digital de pulso LP200 Premium" height="300"></p>

Na imagem abaixo está destacada a localização da EEPROM na placa do circuito.

<p align="center"><img src="https://raw.githubusercontent.com/Andreick/blood-pressure-monitor-hack/assets/imgs/circuito_LP200.png" alt="Placa do LP200 Premium com o microcontrolador e a EEPROM circulados" height="300"></p>
