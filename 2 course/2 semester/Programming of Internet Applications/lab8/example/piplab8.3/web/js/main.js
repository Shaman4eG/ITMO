const imageClick = (event) => {
    console.log('click!');
    const r = window.document.getElementById('displayR').innerHTML;

    console.log(event.offsetX, event.offsetY);

    let res = getCoordinates(event.offsetX, event.offsetY, r);

    const xGraphInput = window.document.getElementById('graph-form:graphX');
    xGraphInput.value = res.x;

    const yGraphInput = window.document.getElementById('graph-form:graphY');
    yGraphInput.value = res.y;

    console.log(res.x, res.y);

    let submitButton = window.document.getElementById("graph-form:graph-submit");
    submitButton.click();
};
const getCoordinates = (offsetX, offsetY, r) => {
    const parent = window.document.getElementById('graph-form:image');

    const x = r*(offsetX - parent.clientWidth / 2 ) / parent.clientWidth * 2;
    const y = r*(parent.clientHeight / 2 - offsetY) / parent.clientHeight * 2;

    return { x, y };
};

const updateImage = (event) => {
    const points = Array.from(window.document.getElementsByClassName('point-info'));
    const res = points.map((point => {
        let children = Array.from(point.childNodes).filter(elem => elem.localName === 'td');
        console.log(children);
        return {
            x: children[0].innerHTML,
            y: children[1].innerHTML,
            fit: children[2].innerHTML
        };
    }));

    clearAllDots();
    setNewDots(res);

    console.log(res);
};
const setNewDots = (res) => {
    const r = window.document.getElementById('displayR').innerHTML;
    const imageElement = window.document.getElementById('image-container');

    res.forEach(pointInfo => {
        const point = window.document.createElement('div');
        point.classList.add('point');
        point.classList.add(pointInfo.fit === 'true' ? 'in' : 'out');
        const offset = getOffset(pointInfo.x, pointInfo.y, r);
        point.style.top = offset.offsetY + "px";
        point.style.left = offset.offsetX + "px";
        console.log(offset);
        imageElement.appendChild(point);
    });
};
const clearAllDots = () => {
  const imageContainer = window.document.getElementById('image-container');
  console.log("clear dots");
  while (imageContainer.lastChild && imageContainer.lastChild.localName === 'div') {
      imageContainer.removeChild(imageContainer.lastChild);
  }
};

const getOffset = (x, y, r) => {
    const parent = window.document.getElementById('graph-form:image');

    const offsetX = x / r * parent.clientWidth / 2 + parent.clientWidth / 2;
    const offsetY = -y / r * parent.clientHeight / 2 + parent.clientHeight / 2;

    return {offsetX, offsetY };
};

updateImage();
