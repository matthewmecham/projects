//Matthew Mecham - Program 4 - 12/8/2019
package com.company;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Burger extends Ingredients {
    protected String [] buns;
    protected String [] condiments;
    protected int bun_count;
    protected int condiment_count;

    Burger()
    {
       super();
       read_cheeses();
       read_proteins();
       read_veggies();
       read_starch();
       read_sauce();
    }

    public void special()
    {
        System.out.println("---------------------- DAILY SPECIAL ------------------------");
        this.rand = random.nextInt(bun_count);
        System.out.println("Bun: " + buns[this.rand]);
        this.rand = random.nextInt(protein_count);
        System.out.println("Protein: " + protein[this.rand]);
        this.rand = random.nextInt(condiment_count);
        System.out.println("Condiment: " + condiments[this.rand]);
        this.rand = random.nextInt(cheese_count);
        System.out.println("Cheese: " + cheese[this.rand]);
        this.rand = random.nextInt(veggie_count);
        System.out.println("Veggie: " + veggies[this.rand]);
        System.out.println("-------------------------------------------------------------");
        System.out.println();
    }

    protected void read_veggies()
    {
        int i = 0;
        this.veggie_count = 0;
        try
        {
            input = new Scanner(new File("burger_veggies.txt"));

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
            input = new Scanner(new File("burger_veggies.txt"));
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
            input = new Scanner(new File("burger_proteins.txt"));

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
            input = new Scanner(new File("burger_proteins.txt"));
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
            input = new Scanner(new File("burger_cheeses.txt"));

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
            input = new Scanner(new File("burger_cheeses.txt"));
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
        this.bun_count = 0;
        try
        {
            input = new Scanner(new File("buns.txt"));

            while (input.hasNextLine())
            {
                input.nextLine();
                ++this.bun_count;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

        buns = new String[this.bun_count];

        try
        {
            input = new Scanner(new File("buns.txt"));
            while(input.hasNextLine())
            {
                this.buns[i] = input.nextLine();
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
        this.condiment_count = 0;
        try
        {
            input = new Scanner(new File("condiments.txt"));

            while (input.hasNextLine())
            {
                input.nextLine();
                ++this.condiment_count;
            }
            input.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
        }

        condiments = new String[this.condiment_count];

        try
        {
            input = new Scanner(new File("condiments.txt"));
            while(input.hasNextLine())
            {
                this.condiments[i] = input.nextLine();
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
        System.out.println("---------------- BUNS, HUN ----------------");
        for(int i = 0; i < bun_count; ++i)
        {
            System.out.println(i + ". " + buns[i]);
        }
        System.out.println("-----------------------------------------");
        System.out.println();
    }

    public void display_sauce()
    {
        System.out.println("---------------- CONDIMENTS ----------------");
        for(int i = 0; i < condiment_count; ++i)
        {
            System.out.println(i + ". " + condiments[i]);
        }
        System.out.println("-----------------------------------------");
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
        return buns[index];
    }

    public String get_sauce(int index)
    {
        return condiments[index];
    }
}
