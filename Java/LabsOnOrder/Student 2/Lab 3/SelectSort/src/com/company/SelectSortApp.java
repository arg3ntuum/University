package com.company;
import com.company.ArraySel;
import java.util.Scanner;


public class SelectSortApp {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int maxSize = 100; // Розмір масиву
        ArraySel arr; // Посилання на масив
        arr = new ArraySel(maxSize); // Створення масиву
        System.out.println("Введите количество елеметов масива: ");
        int nElements = in.nextInt();
        for (byte i = 0;i < nElements;i++)
            arr.insert((int)(java.lang.Math.random()*10));
        arr.display();
        arr.selectSort();
        arr.display();
        System.out.println("Мода: " + arr.moda(nElements));
    }
}