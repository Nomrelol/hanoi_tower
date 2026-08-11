import java.util.Scanner;

public class TowerOfHanoi {

    // Stack implementation for disk peg
    static class Peg {
        int[] disk;
        int   top = -1;

        Peg(int capacity) { disk = new int[capacity]; }

        void push(int v)     { disk[++top] = v; }
        int  pop()           { return disk[top--]; }
        int  get(int i)      { return disk[i]; }
        int  size()          { return top + 1; }
        boolean isEmpty()    { return top == -1; }
    }

    static int   n;
    static Peg   left, middle, right;
    static int   moves = 0;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of disks (1-8): ");
        n = sc.nextInt();
        if (n < 1 || n > 8) n = 3;

        left   = new Peg(n);
        middle = new Peg(n);
        right  = new Peg(n);

        for (int i = n; i >= 1; i--) left.push(i);

        System.out.println("\nInitial State:\n");
        show();

        move(n, left, right, middle, "A", "C", "B");

        System.out.println("Solved in " + moves + " moves!");
        sc.close();
    }

    static void move(int k, Peg from, Peg to, Peg helper,
                     String nameFrom, String nameTo, String nameHelper) {
        if (k == 1) {
            to.push(from.pop());
            moves++;
            System.out.println("Move disk 1: " + nameFrom + " -> " + nameTo + "\n");
            show();
            return;
        }
        move(k - 1, from, helper, to, nameFrom, nameHelper, nameTo);
        to.push(from.pop());
        moves++;
        System.out.println("Move disk " + k + ": " + nameFrom + " -> " + nameTo + "\n");
        show();
        move(k - 1, helper, to, from, nameHelper, nameTo, nameFrom);
    }

    static void show() {
        for (int lvl = n; lvl >= 1; lvl--) {
            printLevel(left,   lvl);
            printLevel(middle, lvl);
            printLevel(right,  lvl);
            System.out.println();
        }
        for (int i = 0; i < n * 8 + 5; i++) System.out.print('-');
        System.out.println();
        System.out.printf("%" + n + "sA%" + (n + 7) + "sB%" + (n + 7) + "sC%n%n", "", "", "");
    }

    static void printLevel(Peg rod, int lvl) {
        if (rod.size() >= lvl) {
            int d = rod.get(lvl - 1);
            int spaces = n - d;
            for (int i = 0; i < spaces; i++) System.out.print(' ');
            for (int i = 0; i < d * 2 - 1; i++) System.out.print('*');
            for (int i = 0; i < spaces; i++) System.out.print(' ');
        } else {
            for (int i = 0; i < n - 1; i++) System.out.print(' ');
            System.out.print('|');
            for (int i = 0; i < n - 1; i++) System.out.print(' ');
        }
        System.out.print("    ");
    }
}
