# Leitor RFID com LCD para Controle de Acesso

Este projeto Arduino implementa um sistema básico de controle de acesso utilizando um módulo **RFID-RC522** e um display **LCD 16x2** com interface I2C. Ele lê o UID (Unique Identifier) de tags RFID/NFC e exibe mensagens de "Acesso Negado" ou "Acesso Concedido" com o UID da tag no LCD.

## Funcionalidades

- **Leitura de Tags RFID/NFC:** Detecta e lê tags que se aproximam do módulo MFRC522.
- **Exibição no LCD:** Mostra mensagens claras no display LCD sobre o status do acesso (negado ou concedido) e o UID da tag.
- **Saída Serial:** Imprime informações detalhadas da tag (tipo e UID) no Monitor Serial para depuração.
- **Indicação Visual:** Inicia com "Acesso Negado" e muda para "Acesso Concedido" ao ler uma tag, voltando ao estado inicial após um tempo.

## Componentes Necessários

- Arduino Uno
- Módulo RFID-RC522
- Display LCD 16x2 com módulo I2C
- Protoboard para organização

## Ligações

As conexões são cruciais para o funcionamento correto do projeto.

### Módulo RFID-RC522 ao Arduino

| MFRC522 Pino | Arduino Pino (Exemplo para Uno) |
|--------------|-------------------------------|
| SDA (SS)     | D10                           |
| SCK          | D13                           |
| MOSI         | D11                           |
| MISO         | D12                           |
| RST          | D5                            |
| 3.3V         | 3.3V                          |
| GND          | GND                           |

### Display LCD I2C ao Arduino

| LCD I2C Pino | Arduino Pino (Exemplo para Uno) |
|--------------|-------------------------------|
| SDA          | A4                            |
| SCL          | A5                            |
| VCC          | 5V                            |
| GND          | GND                           |

## Bibliotecas

Para compilar e executar este código, você precisará das seguintes bibliotecas instaladas na sua IDE Arduino:

- **MFRC522:** Para interagir com o módulo RFID-RC522. [GitHub - Miguel Balboa](https://github.com/miguelbalboa/rfid)
- **LiquidCrystal I2C:** Para controlar o display LCD com interface I2C. [GitHub - Frank de Brabander](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)
- **SPI:** Geralmente já vem inclusa com a IDE Arduino.
- **Wire:** Essencial para a comunicação I2C, também geralmente já vem inclusa.

## Configuração do Código

- `#define SS_PIN 10` e `#define RST_PIN 5`: Estes são os pinos de Slave Select (SS) e Reset (RST) para o módulo RFID. Você pode ajustá-los se suas conexões forem diferentes.
- `LiquidCrystal_I2C lcd(0x27, 16, 2);`: O `0x27` é o endereço I2C do seu módulo LCD. Os endereços mais comuns são `0x27` ou `0x3F`. Se o seu LCD não estiver funcionando, tente alterar este valor. O `16, 2` indica que é um LCD de 16 colunas e 2 linhas.

## Como Usar

1. **Monte o Circuito:** Conecte todos os componentes ao seu Arduino conforme as instruções de ligação acima.
2. **Abra o Código:** Copie o código fornecido para a sua IDE Arduino.
3. **Instale as Bibliotecas:** Certifique-se de que todas as bibliotecas necessárias estão instaladas.
4. **Selecione a Placa e a Porta:** No menu Ferramentas da IDE Arduino, selecione a sua placa Arduino (ex: Arduino Uno) e a porta serial correta.
5. **Carregue o Código:** Clique no botão "Upload" (seta para a direita) para carregar o código para o seu Arduino.

### Teste

- O LCD deve exibir "Acesso Negado".
- Abra o Monitor Serial (**Ferramentas > Monitor Serial**) e defina a taxa de baud para 9600. Você verá a mensagem "Tap RFID/NFC Tag on reader".
- Aproxime uma tag RFID/NFC do leitor MFRC522.
- No LCD, a mensagem mudará para "Acesso Concedido para:" e exibirá o UID da tag.
- No Monitor Serial, o tipo da tag e o UID serão impressos.
- Após 5 segundos, o LCD voltará a exibir "Acesso Negado".