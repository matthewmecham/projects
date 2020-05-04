//Matthew Mecham - Program 4 - 12/8/2019
package com.company;

public class Node {
    protected String choice;
    protected Node next;

    Node(String choice, Node next)
    {
        this.choice = choice;
        this.next = next;
    }
    public Node get_next()
    {
        return next;
    }

    public void set_next(Node connection)
    {
        next = connection;
    }

    public void display()
    {
        System.out.print(choice);
    }
}
