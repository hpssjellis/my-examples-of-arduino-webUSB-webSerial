```

function callTransfer(temp1) {
    temp1.controlTransferOut({
        requestType: 'standard',
        recipient: 'device',
        request: 0x07,
        value: 0x08,
        index: 0x04
    })
        .then(() => {
            console.log('sent req'); device.transferIn(1, 32)
        }) // Waiting for 32 bytes of data from endpoint #1.
        .then(result => {
            console.log(result);
        })
        .catch(error => {
            console.log(error);
        });
}

navigator.usb.requestDevice({
    filters: [{}]
}).then((selectedDevice) => {
    device = selectedDevice;
    return device.open()
        .then(() => device.reset())
        .then(() => device.selectConfiguration(1))
        .then(() => device.claimInterface(device.configuration.interfaces[0].interfaceNumber))
        .then(() => {
            callTransfer(device);
        })
});

```
