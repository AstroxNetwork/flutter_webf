describe('Transform translate', () => {
  it('001', async () => {
    document.body.appendChild(
      createElementWithStyle('div', {
        width: '100px',
        height: '100px',
        backgroundColor: 'red',
        transform: 'translate(10px, 6px )',
      })
    );

    await snapshot();
  });

  it('should work with percentage with one value', async () => {
    let div;
    div = createElement(
      'div',
      {
        style: {
          width: '200px',
          height: '200px',
          backgroundColor: 'yellow',
          position: 'relative',
        },
      },
      [
        createElement('div', {
          style: {
            width: '100px',
            height: '100px',
            transform: 'translate(40%)',
            backgroundColor: 'green',
          }
        })
      ]
    );

    BODY.appendChild(div);
    await snapshot();
  });

  it('should work with percentage with one value when dynamic created', async (done) => {
    let div;
    div = createElement(
      'div',
      {
        style: {
          width: '200px',
          height: '200px',
          backgroundColor: 'yellow',
          position: 'relative',
        },
      },
      [
        createElement('div', {
          style: {
            transform: 'translate(40%)',
            backgroundColor: 'green',
          }
        }, [
          createText('TEXT TEXT')
        ])
      ]
    );
    requestAnimationFrame(async () => {
      BODY.appendChild(div);
      await snapshot();
      done();
    });
  });

  it('should work with percentage with two values', async () => {
    let div;
    div = createElement(
      'div',
      {
        style: {
          width: '200px',
          height: '200px',
          backgroundColor: 'yellow',
          position: 'relative',
        },
      },
      [
        createElement('div', {
          style: {
            width: '100px',
            height: '100px',
            transform: 'translate(40%, 20%)',
            backgroundColor: 'green',
          }
        })
      ]
    );

    BODY.appendChild(div);
    await snapshot();
  });

  it('should work with percentage translate and percentage sizing in flow layout', async () => {
    let div;
    div = createElement(
      'div',
      {
        style: {
          width: '200px',
          height: '200px',
          backgroundColor: 'yellow',
          position: 'relative',
        },
      },
      [
        createElement('div', {
          style: {
            width: '100%',
            height: '100%',
            transform: 'translate(40%, 40%)',
            backgroundColor: 'green',
          }
        })
      ]
    );

    BODY.appendChild(div);
    await snapshot();
  });

  it('should work with percentage translate and percentage sizing in flex layout', async () => {
    let div;
    div = createElement(
      'div',
      {
        style: {
          display: 'flex',
          width: '200px',
          height: '200px',
          backgroundColor: 'yellow',
          position: 'relative',
        },
      },
      [
        createElement('div', {
          style: {
            width: '100%',
            height: '100%',
            transform: 'translate(40%, 40%)',
            backgroundColor: 'green',
          }
        })
      ]
    );

    BODY.appendChild(div);
    await snapshot();
  });

  it('should work with percentage after element is attached', async (done) => {
    let div2;
    let div;
    div = createElement(
      'div',
      {
        style: {
          display: 'flex',
          width: '200px',
          height: '200px',
          backgroundColor: 'yellow',
          position: 'relative',
        },
      },
      [
        (div2 = createElement('div', {
          style: {
            width: '100%',
            height: '100%',
            backgroundColor: 'green',
          }
        }))
      ]
    );

    BODY.appendChild(div);

    await snapshot();

    requestAnimationFrame(async () => {
       div2.style.transform = 'translate(40%, 40%)';
       await snapshot();
       done();
    });
  });

  it('should be scrollWidth equal clientWidth', async () => {
    let div2;
    let div;
    BODY.style.width = '100%';
    BODY.style.height = '100vh';
    div = createElement(
      'div',
      {
        style: {
          width: '100%',
          height: '100vh',
          position: 'relative',
        },
      },
      [
        (div2 = createElement('div', {
          style: {
            position: 'fixed',
            width: '300px',
            height: '300px',
            top: '50%',
            left: '50%',
            transform: 'translate(-50%, -50%)',
            backgroundColor: 'green',
          }
        }))
      ]
    );
    BODY.appendChild(div);
    expect(div.clientWidth === div.scrollWidth).toBe(true);

  });

   it('should work when update size with transform percentage', async () => {
    const div = createElement('div', {
      style: {
        position: 'absolute',
        padding: '10px 20px',
        border: '1px solid #000',
        left: '50%',
        transform: 'translate(-50%)'
      }
    }, [
      createText('ABC')
    ]);
    document.body.appendChild(div);
    await snapshot()

    div.textContent = 'LONGER TEXT LONGER TEXT';
    await snapshot();
  });
});
