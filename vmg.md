# VMG

### Unknown position problem

When you want make a GUI for this game, there is a subtle but huge problem. That is, the position of the vertexes are no defined and if you place them randomly, an odd and ugly shape will appear.

![Confusing...](.gitbook/assets/image%20%281%29.png)



### FDG Drawing

**Force-directed graph drawing** algorithms are a class of algorithms for drawing graphs in an aesthetically-pleasing way. Their purpose is to position the nodes of a graph in two-dimensional or three-dimensional space so that all the edges are of more or less equal length and there are as few crossing edges as possible, by assigning forces among the set of edges and the set of nodes, based on their relative positions, and then using these forces either to simulate the motion of the edges and nodes or to minimize their energy.

Basically with FDG drawing of the graph, you can solve the issue of ugly graphs.

![A nice graph!](.gitbook/assets/image%20%284%29.png)

### Visual Matrix Generator

As you may have guessed, there is a file named VMG in this game's files. It's a `Visual Matrix Generator.`

You can open `index.html` file and start drawing a matrix. What this little program does is that it creates a graph with force-directed algorithm.

{% hint style="info" %}
Try opening the index.html and try it yourself!
{% endhint %}

You can select a node and hit `B` to mark as **butterfly**.

You can also select a node and hit `S` to mark as **spider**.

And at last but not least you can hit `Enter` and **get a input** for your C game. This file also **includes the position** of each vertex. This makes it quite easy to word with GUI and have a little nice game!
