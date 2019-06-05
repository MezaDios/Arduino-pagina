
$(document).on('change', '#led1', function (e) {
    if ($(this).is(':checked')) {
        console.log('Led 1: Enabled')
        if ($('#led2').is(':checked')) {
            setTimeout(() => {
                window.location.href = './?led1=ON&&led2=ON'
            }, 1000);
        }
        else {
            setTimeout(() => {
                window.location.href = './?led1=ON'
            }, 1000);
        }
    }
    else {
        if ($('#led2').is(':checked')) {
            setTimeout(() => {
                window.location.href = './?led1=OFF&&led2=ON'
            }, 1000);
        }
        else {
            setTimeout(() => {
                window.location.href = './?led1=OFF'
            }, 1000);
        }
    }
})

$(document).on('change', '#led2', function (e) {
    if ($(this).is(':checked')) {
        console.log('Led 2: Enabled')
        if ($('#led1').is(':checked')) {
            setTimeout(() => {
                window.location.href = './?led1=ON&&led2=ON'
            }, 1000);
        }
        else {
            setTimeout(() => {
                window.location.href = './?led2=ON'
            }, 1000);
        }
    }
    else {
        if ($('#led1').is(':checked')) {
            setTimeout(() => {
                window.location.href = './?led1=ON&&led2=OFF'
            }, 1000);
        }
        else {
            setTimeout(() => {
                window.location.href = './?led2=OFF'
            }, 1000);
        }
    }
})

$(document).on('load', 'body', function (e) {
    $.getJSON('192.168.1.1').done(function (data) {
        data.analog.forEach(element => {
            let row = document.createElement('tr')
            let pin = document.createElement('td')
            let status = document.createElement('td')

            pin.textContent = element.p
            status.textContent = element.s

            row.appendChild(pin)
            row.appendChild(pin)

            $('#tablaAnalogica').appendChild(row)

        });

        data.digital.forEach(element => {
            let row = document.createElement('tr')
            let pin = document.createElement('td')
            let status = document.createElement('td')

            pin.textContent = element.p
            status.textContent = element.s

            row.appendChild(pin)
            row.appendChild(pin)

            $('#tablaDigital').appendChild(row)

        });
    })
})