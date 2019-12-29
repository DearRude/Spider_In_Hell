// Graph processing container
let procGraph = {};

procGraph.getLinks = function(myLinks) {
  answer = [];
  for (myLink of myLinks) {
    let vertexes = [];
    vertexes.push(myLink.source.index);
    vertexes.push(myLink.target.index);
    answer.push(vertexes);
  }
  return answer;
};
procGraph.getNodes = function(allNodes) {
  answer = [];
  for (myNode in allNodes) {
    answer.push(myNode);
  }
  return answer;
};
procGraph.getButterflies = function() {
  // force.stop();
  let allNodes = force.nodes();
  let indexes = [];
  for (myNode of allNodes) {
    let x = myNode.x;
    // console.log(svgNode);
    let svgNode = $(`[cx='${x}'].butterfly`);
    if (svgNode.length) {
      indexes.push(myNode.index);
    }
  }
  // force.start();
  return indexes;
};
procGraph.getSpiders = function() {
  // force.stop();
  let allNodes = force.nodes();
  let indexes = [];
  for (myNode of allNodes) {
    let x = myNode.x;
    // console.log(svgNode);
    let svgNode = $(`[cx='${x}'].spider`);
    if (svgNode.length) {
      indexes.push(myNode.index);
    }
  }
  // force.start();
  return indexes;
};
procGraph.getGraphSize = function() {
  let myGraph = force.nodes();
  return myGraph.length;
};
procGraph.getGraphMatrix = function() {
  let myGraph = this.getNodes(force.nodes());
  let myLinks = this.getLinks(force.links());
  let graphLength = myGraph.length;

  for (i = 0; i < graphLength; i++) {
    myGraph[i] = [];
  }

  for (i in myGraph) {
    for (j = 0; j < graphLength; j++) {
      myGraph[i].push(0);
    }
  }

  for (myLink of myLinks) {
    let x = myLink[0];
    let y = myLink[1];
    myGraph[x][y] = 1;
    myGraph[y][x] = 1;
  }
  return myGraph;
};
procGraph.addButterfly = function() {
  let searchElement = $('.node_selected');
  if (searchElement.length) {
    searchElement.addClass('butterfly');
  }
};
procGraph.addSpider = function() {
  let searchElement = $('.node_selected');
  if (searchElement.length) {
    searchElement.addClass('spider');
  }
};

// preparing a variable to save and download.
procGraph.createExportFile = function() {
  let textToSave = '';
  textToSave += prepareTextToWrite(procGraph.getGraphSize());

  let graphMatrix = procGraph.getGraphMatrix();
  // add each row to textToSave
  for (row of graphMatrix) {
    textToSave += prepareTextToWrite(arrayToText(row));
  }

  let spiders = procGraph.getSpiders();
  // Add number of spiders
  textToSave += prepareTextToWrite(spiders.length);
  if (spiders.length) {
    // Add index of spiders
    textToSave += prepareTextToWrite(arrayToText(spiders));
  }

  let butterflies = procGraph.getButterflies();

  // Add number of butterflies
  textToSave += prepareTextToWrite(butterflies.length);
  if (butterflies.length) {
    // Add index of butterflies
    textToSave += prepareTextToWrite(arrayToText(butterflies));
  }

  // Only for ebrahim
  // Save position of each node
  let newNodes = force.nodes();
  for (myNode of newNodes) {
    let px = Math.floor(myNode.px);
    let py = Math.floor(myNode.py);
    let text = `${myNode.index} ${px} ${py}`;
    textToSave += prepareTextToWrite(text);
  }

  // saving Data and download it!
  saveFile(textToSave);
};

// Enable hotkeys
window.addEventListener('keydown', e => {
  key = e.key;
  // console.log(key);
  switch (key) {
    case 'b':
      procGraph.addButterfly(key);
      break;
    case 's':
      procGraph.addSpider(key);
      break;
    case 'Enter':
      procGraph.createExportFile();
  }
});

// Download the text that is given to it
function saveFile(text) {
  var pom = document.createElement('a');
  pom.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
  pom.setAttribute('download', 'graphData');

  pom.style.display = 'none';
  document.body.appendChild(pom);
  pom.click();
  document.body.removeChild(pom);
}
// Only add a \n to the end of the text
function prepareTextToWrite(text) {
  return text + '\n';
}
// It turns an array into string
function arrayToText(arr) {
  let text = '';
  for (i = 0; i < arr.length; i++) {
    text += arr[i];
    if (i != arr.length - 1) {
      text += ' ';
    }
  }
  return text;
}
