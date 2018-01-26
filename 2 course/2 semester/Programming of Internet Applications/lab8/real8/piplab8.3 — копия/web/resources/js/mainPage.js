function createPlane()
{
    var canvas = document.getElementById("plane");
    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    var centerX = canvas.width / 2;
    var centerY = canvas.height / 2;
    var fillColor = "#6b9ff4";
    var inputR = $("#input input[type='radio']:checked").val();//$('#rForButtonSetJs').val();
    document.getElementById('myForm:hiddenR').value = inputR;
    var multiplierOfR = 25;
    var finalR = inputR * multiplierOfR;

    draw(canvas, ctx, centerX, centerY, finalR, fillColor);

    //drawPoint("buttonPoint");
}

function draw(canvas, ctx, centerX, centerY, R, fillColor)
{
    // Top-left square
    ctx.fillStyle = fillColor;
    ctx.fillRect(centerX, centerY, -R, -R);

    // Bottom-right arc
    ctx.beginPath();
    ctx.arc(centerX, centerY, R / 2, 0, Math.PI);
    ctx.fillStyle = fillColor;
    ctx.closePath();
    ctx.fill();
    ctx.clearRect(centerX, centerY, -R / 2, R / 2);

    // Bottom-left triangle
    ctx.beginPath();
    ctx.moveTo(centerX, centerY);
    ctx.lineTo(centerX, centerY + R);
    ctx.lineTo(centerX - R, centerY);
    ctx.closePath();
    ctx.fill();

    ctx.fillStyle = "#000000";
    // Horizontal line
    ctx.fillRect(centerX, 0, 1, canvas.height);
    // Vertical line
    ctx.fillRect(0, centerY, canvas.width, 1);

    ctx.fillStyle = "#000000";
    // Hatches on horizontal line
    ctx.fillRect(centerX - R, centerY - 4, 1, 8);
    ctx.fillRect(centerX - R / 2, centerY - 4, 1, 8);
    ctx.fillRect(centerX + R / 2, centerY - 4, 1, 8);
    ctx.fillRect(centerX + R, centerY - 4, 1, 8);

    // Hatches on vertical line
    ctx.fillRect(centerX - 4, centerY - R, 8, 1);
    ctx.fillRect(centerX - 4, centerY - R / 2, 8, 1);
    ctx.fillRect(centerX - 4, centerY + R / 2, 8, 1);
    ctx.fillRect(centerX - 4, centerY + R, 8, 1);
}

function drawPoint(x, y, hit) {

}

function getClickedPoint(canvas, event) {
    var rect = canvas.getBoundingClientRect();
    var x = Math.round(event.clientX - rect.left - canvas.width / 2 - 1);
    var y = Math.round( - event.clientY + rect.top + canvas.height / 2 + 1);


    document.getElementById('myForm:hiddenX').value = x;
    document.getElementById('myForm:hiddenY').value = y;

    $("#myForm\\:commitClick").click();
}

