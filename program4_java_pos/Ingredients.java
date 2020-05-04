//Matthew Mecham - Program 4 - 12/8/2019
package com.company;
import java.io.*;
import java.rmi.activation.ActivationGroup_Stub;
import java.util.Scanner;
import java.util.Random;

public abstract class Ingredients {
    protected Random random;
    protected Scanner input;
    protected int rand;
    protected int veggie_count;
    protected int protein_count;
    protected int cheese_count;
    protected String [] protein;
    protected String [] cheese;
    protected String [] veggies;

    //constructor
    Ingredients()
    {
        int veggie_count = 0;
        int protein_count = 0;
        int cheese_count = 0;
        random = new Random();
    }

    //Will be overridden by children to create specials
    abstract public void special();

    //Reads from external file to populate veggies array
    //I saw a TON of examples telling me to use the ArrayList class
    //but I thought that it might be cheating a little bit and it was quite a pain to get this working.
    //All of these reads work the same way: first it gets the amount of lines in the corresponding file
    //Second: It makes the corresponding array the appropriate size
    //Finally: It populates the array with the strings from the file. Woo
    abstract protected void read_veggies();

    //Reads from external file to populate protein array
    abstract protected void read_proteins();

    //Reads from external file to populate cheese array
    abstract protected void read_cheeses();

    //displays veggie options
    abstract public void display_veggies();

    //displays protein options
    abstract public void display_proteins();

    //displays cheese options
    abstract public void display_cheeses();

    abstract public void display_starch();

    abstract public void display_sauce();

    abstract public String get_veggie(int index);

    abstract public String get_protein(int index);

    abstract public String get_cheese(int index);

    abstract public String get_starch(int index);

    abstract public String get_sauce(int index);
}

