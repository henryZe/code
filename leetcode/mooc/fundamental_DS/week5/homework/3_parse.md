
~~~ C
int WPL(HuffmanTree T, int Depth)
{
    if (!T->left)
        return Depth * T->weight;
    else
        return WPL(T->left, Depth + 1) + WPL(T->right, Depth + 1);
}
~~~
