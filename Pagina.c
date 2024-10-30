#include <WiFiS3.h>

    const char* ssid = "HONOR X6a Plus";
    const char* password = "gustavo cerati";
    
    WiFiServer server(80);
    const char* externalURL = "https://tu-usuario.github.io/mi-servidor-web"; // URL de tu GitHub Pages
    
    void setup() {
      Serial.begin(115200);
      WiFi.begin(ssid, password);
    
      int max_retries = 20;
      int retries = 0;
    
      while (WiFi.status() != WL_CONNECTED && retries < max_retries) {
        delay(1000);
        Serial.print(".");
        retries++;
      }
    
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConectado a la red WiFi.");
        server.begin();
        Serial.println("Servidor HTTP iniciado.");
      } else {
        Serial.println("\nNo se pudo conectar a la red WiFi.");
      }
    }
    
    void loop() {
      WiFiClient client = server.available();
    
      if (client) {
        Serial.println("Cliente conectado.");
        client.println("HTTP/1.1 302 Found");
        client.print("Location: ");
        client.println(externalURL);
        client.println("Connection: close");
        client.println();
        client.stop();
        Serial.println("Cliente redirigido a sitio externo.");
      }
    }
    