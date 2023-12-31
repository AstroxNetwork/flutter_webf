describe('background-repeat', () => {
  it('default should be repeat', async () => {
    // repeat
    const repeat = document.createElement('div');
    setElementStyle(repeat, {
      width: '360px',
      height: '200px',
      marginTop: '10px',
      display: 'flex',
      flexDirection: 'row',
    });

    const div1 = document.createElement('div');
    setElementStyle(div1, {
      width: '360px',
      height: '200px',
      backgroundImage:
        'url("assets/rabbit.png")',
    });
    repeat.appendChild(div1);
    document.body.appendChild(repeat);
    await sleep(0.1);
    await snapshot(repeat);
  });

  it('none-repeat', async () => {
    // repeat
    const repeat = document.createElement('div');
    setElementStyle(repeat, {
      width: '360px',
      height: '200px',
      marginTop: '10px',
      display: 'flex',
      flexDirection: 'row',
    });

    const div1 = document.createElement('div');
    setElementStyle(div1, {
      width: '360px',
      height: '200px',
      backgroundImage:
        'url(assets/rabbit.png)',
      backgroundRepeat: 'no-repeat',
    });
    repeat.appendChild(div1);
    document.body.appendChild(repeat);
    await sleep(0.1);
    await snapshot(repeat);
  });

  it('repeat-x', async () => {
    const repeat = document.createElement('div');
    setElementStyle(repeat, {
      width: '360px',
      height: '200px',
      marginTop: '10px',
      display: 'flex',
      flexDirection: 'row',
    });

    const div2 = document.createElement('div');
    setElementStyle(div2, {
      width: '360px',
      height: '200px',
      backgroundImage:
        'url(assets/rabbit.png)',
      backgroundRepeat: 'repeat-x',
    });
    repeat.appendChild(div2);
    append(BODY, repeat);
    await sleep(0.2);
    await snapshot(repeat);
  });

  it('repeat-y', async () => {
    const repeat = document.createElement('div');
    setElementStyle(repeat, {
      width: '360px',
      height: '200px',
      marginTop: '10px',
      display: 'flex',
      flexDirection: 'row',
    });

    const div3 = document.createElement('div');
    setElementStyle(div3, {
      width: '360px',
      height: '200px',
      backgroundImage:
        'url(assets/rabbit.png)',
      backgroundRepeat: 'repeat-y',
    });
    repeat.appendChild(div3);
    append(BODY, repeat);
    await sleep(0.2);
    await snapshot(repeat);
  });

  it('repeat', async () => {
    const repeat = document.createElement('div');
    setElementStyle(repeat, {
      width: '360px',
      height: '200px',
      marginTop: '10px',
      display: 'flex',
      flexDirection: 'row',
    });

    const div4 = document.createElement('div');
    setElementStyle(div4, {
      width: '360px',
      height: '200px',
      backgroundImage:
        'url(assets/rabbit.png)',
      backgroundRepeat: 'repeat',
    });
    repeat.appendChild(div4);
    await sleep(0.2);
    append(BODY, repeat);
    await sleep(0.2);
    await snapshot(repeat);
  });

  // @TODO: Support background-repeat: round.
  xit('round', async () => {
    let div = createElementWithStyle('div', {
      width: '220px',
      height: '220px',
      backgroundColor: 'red',
      backgroundImage:
        'url(assets/cat.png)',
      backgroundRepeat: 'round',
    });
    append(BODY, div);
    await sleep(0.5);
    await snapshot(div);
  });

  // @TODO: Support background-repeat: round.
  xit('no-repeat will stop round to repeat', async () => {
    let div = createElementWithStyle('div', {
      width: '220px',
      height: '220px',
      backgroundColor: 'red',
      backgroundImage:
        'url(assets/cat.png)',
      backgroundRepeat: 'round',
    });
    append(BODY, div);
    await sleep(0.5);
    await snapshot(div);
  });

  it("computed", async () => {
    let target;
    target = createElement('div', {
      id: 'target',
      style: {
        'box-sizing': 'border-box',
      },
    });
    BODY.appendChild(target);

    test_computed_value('background-repeat', 'repeat-x');
    test_computed_value('background-repeat', 'repeat-y');
    test_computed_value('background-repeat', 'repeat');
    // test_computed_value('background-repeat', 'space');
    // test_computed_value('background-repeat', 'round');
    test_computed_value('background-repeat', 'no-repeat');

    // test_computed_value('background-repeat', 'repeat space');
    // test_computed_value('background-repeat', 'round no-repeat');

    // See background-computed.html for a test with multiple background images.
    test_computed_value(
      'background-repeat',
      'repeat-x'
    );
  })
});
