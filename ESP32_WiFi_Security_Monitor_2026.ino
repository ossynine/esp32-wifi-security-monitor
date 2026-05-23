#include <WiFi.h>
#include <WebServer.h>

// Create a web server listening on port 80
WebServer server(80);

// Function to translate the raw encryption byte into readable text
// This helps identify insecure Wi-Fi networks
String translateEncryptionType(wifi_auth_mode_t encryptionType) {
  switch (encryptionType) {
    case WIFI_AUTH_OPEN: return "Open (INSECURE)";
    case WIFI_AUTH_WEP: return "WEP (INSECURE)";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2 Enterprise";
    case WIFI_AUTH_WPA3_PSK: return "WPA3";
    default: return "Unknown";
  }
}

// Function that builds and serves the HTML dashboard
void handleRoot() {
  // Start building the HTML response
  String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Wi-Fi Security Scanner</title>";
  
  // CSS Styling (Dark terminal aesthetic)
  html += "<style>";
  html += "body { font-family: 'Courier New', monospace; background-color: #121212; color: #00ff00; padding: 20px; }";
  html += "h1 { border-bottom: 1px solid #00ff00; padding-bottom: 10px; }";
  html += "table { width: 100%; border-collapse: collapse; margin-top: 20px; }";
  html += "th, td { border: 1px solid #333; padding: 10px; text-align: left; }";
  html += "th { background-color: #1e1e1e; }";
  html += ".insecure { color: #ff3333; font-weight: bold; }"; // Red text for vulnerable networks
  html += "button { background-color: #00ff00; color: #121212; border: none; padding: 10px 20px; font-size: 16px; cursor: pointer; font-family: 'Courier New', monospace; font-weight: bold; margin-top: 20px; }";
  html += "button:hover { background-color: #00cc00; }";
  html += "</style></head><body>";
  
  html += "<h1>ESP32 Network Reconnaissance</h1>";
  html += "<p>Scanning nearby Wi-Fi networks and device activity...</p>";

  // Execute the Wi-Fi Scan
  int n = WiFi.scanNetworks();
  
  if (n == 0) {
    html += "<p>No networks found in range.</p>";
  } else {
    html += "<p>Total Networks Discovered: " + String(n) + "</p>";
    html += "<table><tr><th>SSID (Network Name)</th><th>BSSID (MAC Address)</th><th>Signal (RSSI)</th><th>Security Protocol</th></tr>";
    
    // Loop through all discovered networks and populate the table
    for (int i = 0; i < n; ++i) {
      String securityStr = translateEncryptionType(WiFi.encryptionType(i));
      
      // Apply a CSS class to highlight insecure networks in red
      String rowClass = (securityStr.indexOf("INSECURE") > -1) ? "class='insecure'" : "";
      
      html += "<tr " + rowClass + ">";
      html += "<td>" + WiFi.SSID(i) + "</td>";
      html += "<td>" + WiFi.BSSIDstr(i) + "</td>"; // Important for device detection
      html += "<td>" + String(WiFi.RSSI(i)) + " dBm</td>"; // Monitor unexpected signal changes
      html += "<td>" + securityStr + "</td>";
      html += "</tr>";
    }
    html += "</table>";
  }
  
  // Button to refresh the page and trigger a new scan
  html += "<button onclick='location.reload()'>Initialize New Scan</button>";
  html += "</body></html>";

  // Send the completed HTML to the browser
  server.send(200, "text/html", html);
}

void setup() {
  // Start the serial monitor for debugging
  Serial.begin(115200);
  
  // Configure ESP32 to act as BOTH an Access Point (to host the site) and a Station (to scan)
  WiFi.mode(WIFI_AP_STA); 
  
  // Setup the ESP32's own Wi-Fi network
  // Format: WiFi.softAP("Network_Name", "Password");
  WiFi.softAP("ESP32_Security_Monitor", "admin1234"); 

  Serial.println("\n--- ESP32 Security Monitor Started ---");
  Serial.print("Connect your device to Wi-Fi network: ESP32_Security_Monitor\n");
  Serial.print("Password: admin1234\n");
  Serial.print("Then open a browser and go to IP: ");
  Serial.println(WiFi.softAPIP());

  // Tell the web server what to do when someone visits the root page ("/")
  server.on("/", handleRoot);
  
  // Start the web server
  server.begin();
  Serial.println("HTTP local dashboard running.");
}

void loop() {
  // Constantly listen for incoming web browser connections
  server.handleClient();
}