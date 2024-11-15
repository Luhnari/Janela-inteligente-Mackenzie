# Janela Inteligente com Sensor de Chuva

## Descrição do Projeto

Este projeto apresenta o desenvolvimento de uma janela inteligente automatizada que fecha automaticamente ao detectar chuva, utilizando um microcontrolador NodeMCU ESP8266, um sensor de chuva, e um servo motor. A ideia principal é proteger o ambiente interno de forma autônoma, oferecendo uma solução prática e inteligente para automação industrial e/ou residencial.

Através do sensor de chuva, o sistema é capaz de detectar a presença de água e, automaticamente, aciona o servo motor para fechar a janela. LEDs indicadores são usados para mostrar o status da janela (aberta ou fechada). O projeto também inclui comunicação via protocolo MQTT, permitindo que o status da janela seja monitorado remotamente.

## Funcionalidade e Uso

- **Detecção de Chuva**: Quando o sensor detecta a presença de água, o NodeMCU aciona o servo motor para fechar a janela.
- **Indicadores LED**: O LED verde indica que a janela está aberta (sem chuva), enquanto o LED vermelho indica que a janela foi fechada devido à chuva.
- **Monitoramento Remoto via MQTT**: O sistema utiliza o protocolo MQTT para enviar e receber atualizações sobre o status da janela, permitindo monitoramento remoto.
- **Reprodução**: Para reproduzir este projeto, você precisa montar o hardware conforme descrito abaixo e carregar o código no NodeMCU. Certifique-se de configurar os parâmetros de rede Wi-Fi e do broker MQTT antes de iniciar.

## Hardware Utilizado

### 1. Plataforma de Desenvolvimento
- **NodeMCU ESP8266**: Microcontrolador com conectividade Wi-Fi integrado. Este componente gerencia as leituras do sensor, controla o servo motor e se comunica com a rede MQTT.

### 2. Sensores e Atuadores
- **Sensor de Chuva (FC-37)**: Detecta a presença de água. Quando molhado, reduz a resistência elétrica, indicando a presença de chuva e acionando o fechamento da janela.
- **Servo Motor SG90**: Atuador responsável por simular o movimento de fechamento da janela. É acionado quando o sensor de chuva detecta a presença de água.
- **LEDs Indicadores**: Dois LEDs (vermelho e verde) são usados para indicar o estado da janela:
  - **LED Verde**: Indica que a janela está aberta e que não há presença de chuva.
  - **LED Vermelho**: Indica que a janela foi fechada em resposta à chuva.

### 3. Outros Componentes
- **Protoboard**: Utilizado para a montagem temporária do circuito e conexão dos componentes.
- **Cabos Jumper**: Utilizados para interligar o NodeMCU, o sensor de chuva, o servo motor e os LEDs.
- **Fonte de Alimentação 3.3V**: Recomendada para fornecer energia suficiente ao servo motor.

## Comunicação e Protocolos

### Protocolo MQTT
- O sistema utiliza o protocolo MQTT para comunicação em tempo real. O NodeMCU conecta-se ao broker MQTT (neste caso, `test.mosquitto.org`) e publica o status da janela em um tópico específico.
- **Tópicos MQTT**:
  - `janela/status`: Publica o status atual da janela ("Janela aberta" ou "Janela fechada devido à chuva").
  - `janela/comando`: Permite o envio de comandos para resetar o sistema, retornando o servo motor à posição inicial.

### Interfaces e Módulos Utilizados
- **ESP8266WiFi.h**: Biblioteca para conectar o NodeMCU à rede Wi-Fi.
- **PubSubClient.h**: Biblioteca para o uso do protocolo MQTT com o ESP8266, possibilitando a comunicação com o broker e a publicação/assinatura em tópicos.

## Diagrama de Ligação do Hardware

1. **Sensor de Chuva**: Conectado ao pino `D5` do NodeMCU (GPIO 14).
2. **Servo Motor**: Conectado ao pino `D4` (GPIO 2) para controle de ângulo.
3. **LED Verde**: Conectado ao pino `D1` (GPIO 5).
4. **LED Vermelho**: Conectado ao pino `D2` (GPIO 4).

## Como Usar o Código

1. **Configurar Wi-Fi e MQTT**: Insira o nome e a senha do Wi-Fi, além do endereço do broker MQTT no início do código.
2. **Carregar o Código no NodeMCU**: Utilize o Arduino IDE para carregar o código no NodeMCU.
3. **Monitorar o Serial**: Através do Monitor Serial do Arduino IDE, é possível verificar os status e mensagens de debug.
4. **Monitoramento Remoto**: Conecte-se ao broker MQTT para visualizar o status da janela e enviar comandos remotamente.

## Observações

- Certifique-se de que o sensor de chuva está posicionado de forma que possa ser molhado para simular a detecção de chuva.
- Verifique a alimentação do servo motor, pois ele pode precisar de uma fonte de energia externa se o NodeMCU não fornecer corrente suficiente.

