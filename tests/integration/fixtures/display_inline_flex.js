it('display_inline_flex', () => {
  function setStyle(dom, object) {
    for (let key in object) {
      if (object.hasOwnProperty(key)) {
        dom.style[key] = object[key];
      }
    }
  }

  const container = document.createElement('div');
  setStyle(container, {
    width: '100px',
    height: '100px',
    backgroundColor: '#666',
  });
  container.appendChild(document.createTextNode('inline-flex'));

  document.body.appendChild(container);
  document.body.appendChild(document.createTextNode('test text'));

  requestAnimationFrame(() => {
    container.style.display = 'inline-flex';
    container.style.justifyContent = 'center';
    container.style.alignItems = 'center';
  });
});