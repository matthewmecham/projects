//Matthew Mecham - Program 4 - 12/8/2019
package com.company;
import javax.swing.*;
import java.util.Scanner;

public class Order {
    protected Scanner input;
    protected boolean confirm;
    protected String name;
    protected int choice;
    protected String option;
    protected String burger;
    protected String pizza;
    protected Order left;
    protected Order right;
    protected Node [] head;
    protected int max_item;
    protected int item_count;
    protected int size;
    protected int i;
    Ingredients ingredients;

    Order()
    {
        confirm = false;
        left = null;
        right = null;
        max_item = 0;
        size = 5;
        head = new Node[size];
        i = 0;
        burger = "b";
        pizza = "p";
        item_count = 0;
    }

    protected void add(Node current, String data)
    {
        if (current.get_next() != null)
        {
            add(current.get_next(), data);
        }
        else
        {
           //Node temp = new Node(data, null);
           //current.set_next(temp);
            current.next = new Node(data, null);
        }
    }

    protected void insert(String data)
    {
       if(this.head[i] == null)
       {
           this.head[this.i] = new Node(data, null);
       }
       else
       {
           add(this.head[this.i], data);
       }
    }

    public void display_all()
    {
        this.i = 0;
        display_all(this.head);
    }

    protected void display_list(Node head)
    {
        if(this.head[this.i] == null)
        {
            return;
        }

        if(this.head[this.i].get_next() == null)
        {
            this.head[this.i].display();
            System.out.println();
            return;
        }
        else if(this.head[this.i].get_next() != null)
        {
            this.head[this.i].display();
            System.out.print(" ");
            display_list(this.head[this.i].get_next());
        }
        //else
        //{
         //   display_list(this.head[this.i].get_next());
        //}
    }

    protected void display_all(Node [] head)
    {
        /*if (head[this.i].get_next() == null)
        {
            display_list(head[this.i]);
        }
        if(this.i == size - 1)
        {
           display_list(head[this.i]);
           return;
        }
        else
        {
            ++this.i;
            display_all(head);
        }
       */
        switch (i)
        {
            case 1:
        }
    }

    public void take_order()
    {
        this.i = 0;
        input = new Scanner(System.in);
        System.out.println("Welcome to Matt Mecham's Pizza/Burger shop!");
        System.out.println("Would you like a [B]urger or [P]izza today? (B for Burger and P for Pizza): ");
        option = input.nextLine();

        //Time to build a pizza order if that is what they chose
        if(this.option.equalsIgnoreCase(this.pizza))
        {
            ingredients = new Pizza(); //Dynamic binding

            //Introducing choice and prompting - I would take more time to confirm choice but I am down to the wire
            System.out.println("Mmmm, Pizza! Good choice!" + "\nToday's Pizza Special is: ");
            ingredients.special();
            System.out.println("Can I please get a name for this order?: ");
            name = input.nextLine();
            System.out.println("Thank you, " + name + ". ");
            System.out.println("Now let's build your order.\n" + "First, Let's choose a crust.");
            ingredients.display_starch();
            System.out.println("You may choose one crust. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            //insert they crust choice in index 1 of head array
            insert(ingredients.get_starch(choice));
            ++i; //increment since index 1 of head array will be proteins
            //Prompting for proteins now
            System.out.println("Time to choose a protein");
            ingredients.display_proteins();
            System.out.println("You may choose one protein. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_protein(choice));
            ++i;
            //Prompting for a veggie now
            System.out.println("Time to choose a veggie");
            ingredients.display_veggies();
            System.out.println("You may choose two veggies. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_veggie(choice));
            //prompt for second veggie
            System.out.println("Time to choose another veggie");
            ingredients.display_veggies();
            System.out.println("You may choose one more veggie. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_veggie(choice));
            ++i;
            //Prompting for sauce
            System.out.println("Time to choose a sauce");
            ingredients.display_sauce();
            System.out.println("You may choose one sauce. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_sauce(choice));
            ++i;
            //Prompting for cheese
            System.out.println("Time to choose a cheese");
            ingredients.display_cheeses();
            System.out.println("You may choose two cheeses. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_cheese(choice));
            //Prompt for second cheese
            System.out.println("Time to choose another cheese");
            ingredients.display_cheeses();
            System.out.println("You may choose one more cheese. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_cheese(choice));
            ++i;
        }
        else //They chose burger and I will go through the same steps
        {
            ingredients = new Burger(); //dynamic binding

            //Introducing choice and prompting - I would take more time to confirm choice but I am down to the wire
            System.out.println("Mmmm, Burger! Good choice!" + "\nToday's Burger Special is: ");
            ingredients.special();
            System.out.println("Can I please get a name for this order?: ");
            name = input.nextLine();
            System.out.println("Thank you, " + name + ". ");
            System.out.println("Now let's build your order.\n" + "First, Let's choose a bun.");
            ingredients.display_starch();
            System.out.println("You may choose one bun. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            //insert they crust choice in index 1 of head array
            insert(ingredients.get_starch(choice));
            ++i; //increment since index 1 of head array will be proteins
            //Prompting for proteins now
            System.out.println("Time to choose a protein");
            ingredients.display_proteins();
            System.out.println("You may choose one protein. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_protein(choice));
            ++i;
            //Prompting for a veggie now
            System.out.println("Time to choose a veggie");
            ingredients.display_veggies();
            System.out.println("You may choose two veggies. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_veggie(choice));
            //prompt for second veggie
            System.out.println("Time to choose another veggie");
            ingredients.display_veggies();
            System.out.println("You may choose one more veggie. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_veggie(choice));
            ++i;
            //Prompting for sauce
            System.out.println("Time to choose a sauce");
            ingredients.display_sauce();
            System.out.println("You may choose one sauce. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_sauce(choice));
            ++i;
            //Prompting for cheese
            System.out.println("Time to choose a cheese");
            ingredients.display_cheeses();
            System.out.println("You may choose two cheeses. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_protein(choice));
            //Prompt for second cheese
            System.out.println("Time to choose another cheese");
            ingredients.display_cheeses();
            System.out.println("You may choose one more cheese. Please type the corresponding number: ");
            choice = input.nextInt();
            input.nextLine();
            insert(ingredients.get_cheese(choice));
            ++i;
        }
    }
}

