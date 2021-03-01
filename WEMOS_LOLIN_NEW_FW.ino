/********************************************************************************************************/
/*                    Exemplo funcional para as placas Wemos Lolin ESP32 - Básico                       */
/********************************************************************************************************/

//Bibliotecas básicas para usar a placa
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"

//Imagens - pode-se usar as que você criar
#include "images.h"
#include "images_Willcorp.h"

// Cnfiguração do display
SSD1306Wire display(0x3c, 5, 4);  // ADDRESS: 0x3C, Pinos 5 e 4

int iState;
int iCounter;

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void TextosDiferentesTamanhos() 
{
  display.setTextAlignment(TEXT_ALIGN_LEFT);  //Define alinhamento
  display.setFont(ArialMT_Plain_10);          //Formato Arial, tamanho 10
  display.drawString(0, 0, "Will Corp");
  //Para usar as fonte abaixo, entre no site http://oleddisplay.squix.ch/ 
  //O código criado deverá ser copiado na biblioteca OLEDDisplayFonts.h antes do endif
  //Considere se puder pagar a cerveja do criador do site.
  display.setFont(Aclonica_Regular_16);       //Formato Aclonica, tamanho 16
  display.drawString(0, 15, "Will Corp");
  display.setFont(Coming_Soon_Regular_24);    //Formato Coming_Soon_Regular, tamanho 16
  display.drawString(0, 29, "Will Corp");
  display.display();
  iState    = 0;
  iCounter  = 0;
}

void TextoFluxo() 
{
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawStringMaxWidth(0, 0, 128,
    "Exemplo com texto\n Nesse exemplo vemos um texto escrito por completo no display." );
  display.display();  
}

void AlinhamentoTexto() 
{
  // Text alignment demo
  display.setFont(ArialMT_Plain_10);

  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "Left aligned (0,10)");

  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Center aligned (64,22)");

  // The coordinates define the right end of the text
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, "Right aligned (128,33)");

  display.display();
}

void DesenhaRetangulo() 
{
  // Draw a pixel at given position
  for (int i = 0; i < 10; i++) 
  {
    display.setPixel(i, i);
    display.setPixel(10 - i, i);
  }
  display.drawRect(12, 12, 20, 20);

  // Fill the rectangle
  display.fillRect(14, 14, 17, 17);

  // Draw a line horizontally
  display.drawHorizontalLine(0, 40, 20);

  // Draw a line horizontally
  display.drawVerticalLine(40, 0, 20);
  display.display();
}

void DesenhaCirculo() 
{
  for (int i=1; i < 8; i++) 
  {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i*3);
    if (i % 2 == 0) 
    {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i* 3);
  }
  display.display();
}

void DesenhaProgressiveBar() 
{
  display.setTextAlignment(TEXT_ALIGN_CENTER);        //Define alinhamento
  display.setFont(URW_Chancery_L_Medium_Italic_10);   //Formato Arial, tamanho 10
  display.drawString(64, 0, "Barra status");

  
  int progress = iCounter;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
  display.display();
}

void DesenhaWifiLogo() 
{
  // Para criar suas imagens no formato usado, acesse http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
  display.drawXbm(34, 15, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  display.display();
}

void DesenhaWillcorpLogo() 
{
  // Para criar suas imagens no formato usado, acesse http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
  display.drawXbm(34, 1, Willcorp_width, Willcorp_height, Willcorp_bits);
  display.display();
}

void loop() 
{
  // clear the display
  display.clear();
  switch (iState)
  {
    case 0:
      DesenhaWillcorpLogo();       
      delay(2000);
      iState = 1; 
      break;
    case 1: 
      TextosDiferentesTamanhos();
      delay(2000);
      iState = 2;
      break;
    case 2: 
      TextoFluxo();
      delay(2000);
      iState = 3;
      break;
    case 3: 
      AlinhamentoTexto();
      delay(2000);
      iState = 4;
      break;
    case 4: 
      DesenhaRetangulo();
      delay(2000);
      iState = 5;
      break;
    case 5:
      DesenhaCirculo();
      delay(2000);
      iState = 6; 
      break;
    case 6: 
      while (iCounter < 101)
      {
        display.clear();
        DesenhaProgressiveBar();
        delay(20);
        iCounter++;
      }
      iState = 7;
      delay(1000);
      break;
    case 7: 
      DesenhaWifiLogo();
      delay(2000);
      iState = 0; 
      break;
  }
}
