//Matthew Mecham - Program 4 - 12/8/2019
package com.company;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Pizza extends Ingredients{
    protected String [] crusts;
    protected String [] sauces;
    protected int crust_count;
    protected int sauce_count;

    Pizza()
    {
        super();
        read_cheeses();
        read_proteins();
        read_veggies();
        read_starch();
        read_sauce();
    }

    //Displays a random pizza special
    public void special()
    {
        System.out.println("---------------------- DAILY SPECIAL ------------------------");
        this.rand = random.nextInt(crust_count);
        System.out.println("Crust: " + crusts[this.rand]);
        this.rand = random.nextInt(sauce_count);
        System.out.println("Sauce: " + sauces[this.rand]);
        this.rand = random.nextInt(protein_count);
        System.out.println("Protein: " + protein[this.rand]);
        this.rand = random.nextInt(cheese_count);
        System.out.println("Cheese: " + cheese[this.rand]);
        this.rand = random.nextInt(veggie_count);
        System.out.println("Veggie: " + veggies[this.rand]);
        System.out.println("-------------------------------------------------------------");
        System.out.println();
    }

    //Reads a special pizza_veggies.txt file
    protected void read_veggies()
    {
        int i = 0;
        this.veggie_count = 0;
        try
        {
            input = new Scanner(new File("pizza_veggies.txt"));

            while (input.hasNextLine())
            {
                input.nextLine();
                ++this.veggie_count;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

        veggies = new String[this.veggie_count];

        try
        {
            input = new Scanner(new File("pizza_veggies.txt"));
            while(input.hasNextLine())
            {
                this.veggies[i] = input.nextLine();
                ++i;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }
    }

    protected void read_proteins()
    {
        int i = 0;
        this.protein_count = 0;
        try
        {
            input = new Scanner(new File("pizza_proteins.txt"));

            while (input.hasNextLine())
            {
                input.nextLine();
                ++this.protein_count;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

        protein = new String[this.protein_count];

        try
        {
            input = new Scanner(new File("pizza_proteins.txt"));
            while(input.hasNextLine())
            {
                this.protein[i] = input.nextLine();
                ++i;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }
    }

    protected void read_cheeses()
    {
        int i = 0;
        this.cheese_count = 0;
        try
        {
            input = new Scanner(new File("pizza_cheeses.txt"));

            while (input.hasNextLine())
            {
                input.nextLine();
                ++this.cheese_count;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

        cheese = new String[this.cheese_count];

        try
        {
            input = new Scanner(new File("pizza_cheeses.txt"));
            while(input.hasNextLine())
            {
                this.cheese[i] = input.nextLine();
                ++i;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

    }
    protected void read_starch()
    {
        int i = 0;
        this.crust_count = 0;
        try
        {
            input = new Scanner(new File("crusts.txt"));

            while (input.hasNextLine())
            {
                input.nextLine();
                ++this.crust_count;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

        crusts = new String[this.crust_count];

        try
        {
            input = new Scanner(new File("crusts.txt"));
            while(input.hasNextLine())
            {
                this.crusts[i] = input.nextLine();
                ++i;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }
    }

    protected void read_sauce()
    {
        int i = 0;
        this.sauce_count = 0;
        try
        {
            input = new Scanner(new File("sauces.txt"));

            while (input.hasNextLine())
            {
                input.nextLine();
                ++this.sauce_count;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

        sauces = new String[this.sauce_count];

        try
        {
            input = new Scanner(new File("sauces.txt"));
            while(input.hasNextLine())
            {
                this.sauces[i] = input.nextLine();
                ++i;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }
    }

    public void display_starch()
    {
        System.out.println("------------------ Crusts ------------------");
        for(int i = 0; i < crust_count; ++i)
        {
            System.out.println(i + ". " +crusts[i]);
        }
        System.out.println("-----------------------------------------");
        System.out.println();
    }

    public void display_sauce()
    {
        System.out.println("---------------- Sauces ----------------");
        for(int i = 0; i < sauce_count; ++i)
        {
            System.out.println(i + ". " + sauces[i]);
        }
        System.out.println("---------------------------------------");
        System.out.println();
    }

    public void display_veggies()
    {
        System.out.println("---------------- VEGGIE ----------------");
        for(int i = 0; i < veggie_count; ++i)
        {
            System.out.println(i + ". " + veggies[i]);
        }
        System.out.println("-----------------------------------------");
        System.out.println();
    }

    public void display_cheeses()
    {
        System.out.println("---------------- CHEESE ----------------");
        for(int i = 0; i < cheese_count; ++i)
        {
            System.out.println(i + ". " + cheese[i]);
        }
        System.out.println("-----------------------------------------");
        System.out.println();
    }

    public void display_proteins()
    {
        System.out.println("---------------- PROTEIN ----------------");
        for(int i = 0; i < protein_count; ++i)
        {
            System.out.println(i + ". " + protein[i]);
        }
        System.out.println("-----------------------------------------");
        System.out.println();
    }

    public String get_veggie(int index)
    {
        return veggies[index];
    }

    public String get_protein(int index)
    {
        return protein[index];
    }

    public String get_cheese(int index)
    {
        return cheese[index];
    }

    public String get_starch(int index)
    {
        return crusts[index];
    }

    public String get_sauce(int index)
    {
        return sauces[index];
    }
}
