# my-examples-of-arduino-webusb-webSerial



Single page vanilla javascript source at [public/index.html](public/index.html)


Demo at   https://hpssjellis.github.io/my-examples-of-arduino-webusb-webSerial/public/index.html



```


The difference between the two APIs is how they interface with the operating system to communicate with the device. WebUSB uses the platform-specific USB API while Web Serial uses the platform-specific serial API. This matters because USB is lower level than serial and because not every serial device is a USB device. With WebUSB you will be able to communicate with many different classes of USB device, including serial devices, but it requires the operating system allow the browser to "claim" the USB interface, which means there can't already be a USB device driver present. With Web Serial you will be able to communicate with USB serial devices, but also other types of serial devices such as Bluetooth as well as built-in RS-232 ports and other UARTs. The tradeoff you make with using Web Serial to connect to a USB device is that the operating system needs to have the correct USB serial driver installed so that the device is available through the platform-specific serial API used by the browser to implement Web Serial.




```






## Resources

https://web.dev/usb/  
https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API  
https://codelabs.developers.google.com/codelabs/web-serial#8  




webUSB arduino

```
// Third-party WebUSB Arduino library
#include <WebUSB.h>

WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos");

#define Serial WebUSBSerial

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect.
  }
  Serial.write("WebUSB FTW!");
  Serial.flush();
}

void loop() {
  // Nothing here for now.
}

```

WEbUSB javascript

```
let device;

navigator.usb.requestDevice({ filters: [{ vendorId: 0x2341 }] })
.then(selectedDevice => {
    device = selectedDevice;
    return device.open(); // Begin a session.
  })
.then(() => device.selectConfiguration(1)) // Select configuration #1 for the device.
.then(() => device.claimInterface(2)) // Request exclusive control over interface #2.
.then(() => device.controlTransferOut({
    requestType: 'class',
    recipient: 'interface',
    request: 0x22,
    value: 0x01,
    index: 0x02})) // Ready to receive data
.then(() => device.transferIn(5, 64)) // Waiting for 64 bytes of data from endpoint #5.
.then(result => {
  const decoder = new TextDecoder();
  console.log('Received: ' + decoder.decode(result.data));
})
.catch(error => { console.error(error); });

```




WebSerial Arduino

```
byte incomingByte[1];

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int serialMessage = Serial.parseInt();
    if(serialMessage == 1) {
      Serial.println("LED On");
      digitalWrite(LED_BUILTIN, LOW);
    } else if(serialMessage == 0) {
      Serial.println("LED Off");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}

  

```



WebSerial Javascript 

```
navigator.serial.addEventListener('connect', (e) => {
  // Connect to `e.target` or add it to a list of available ports.
});

navigator.serial.addEventListener('disconnect', (e) => {
  // Remove `e.target` from the list of available ports.
});

navigator.serial.getPorts().then((ports) => {
  // Initialize the list of available ports with `ports` on page load.
});

button.addEventListener('click', () => {
  const usbVendorId = ...;
  navigator.serial.requestPort({ filters: [{ usbVendorId }]}).then((port) => {
    // Connect to `port` or add it to the list of available ports.
  }).catch((e) => {
    // The user didn't select a port.
  });
});

```


or to read a port

```


while (port.readable) {
  const reader = port.readable.getReader();
  try {
    while (true) {
      const { value, done } = await reader.read();
      if (done) {
        // |reader| has been canceled.
        break;
      }
      // Do something with |value|...
    }
  } catch (error) {
    // Handle |error|...
  } finally {
    reader.releaseLock();
  }
}

```

Still looking

https://dev.to/unjavascripter/the-amazing-powers-of-the-web-web-serial-api-3ilc







# WebUSB  API

https://wicg.github.io/webusb/




