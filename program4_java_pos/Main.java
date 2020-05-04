//Matthew Mecham - Program 4 - 12/8/2019
package com.company;

public class Main {

    public static void main(String[] args) {
	// write your code here
        Order order1 = new Order();


        order1.take_order();
        System.out.println("----------------------- Your Order ------------------------");
        order1.display_all();
        System.out.println();
        System.out.println("-----------------------------------------------------------");

    }
}
