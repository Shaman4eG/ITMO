function createPlane()
{
    var canvas = document.getElementById("plane");
    var ctx = canvas.getContext("2d");
    var centerX = canvas.width / 2;
    var centerY = canvas.height / 2;
    var fillColor = "#6b9ff4";
    var inputR = 3;//document.getElementById("demo").innerHTML = "Hello World";
    var multiplierOfR = 25;
    var finalR = inputR * multiplierOfR;

    draw(canvas, ctx, centerX, centerY, finalR, fillColor);


}

function draw(canvas, ctx, centerX, centerY, R, fillColor)
{
    // Top-left square
    ctx.fillStyle = fillColor;
    ctx.fillRect(centerX, centerY, -R, -R);
    ctx.fillRect(centerX, centerY, -R, -R);

    // Bottom-right arc
    ctx.arc(centerX, centerY, R / 2, 0, Math.PI);
    ctx.fillStyle = fillColor;
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

/*
function getClickedPoint(canvas, event) {
    var rect = canvas.getBoundingClientRect();
    var x = Math.round(event.clientX - rect.left);
    var y = Math.round(event.clientY - rect.top);

    console.log("x: " + x + " y: " + y);
}
*/
