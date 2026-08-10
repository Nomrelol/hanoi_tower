import java.util.Scanner;
import java.util.Stack;

public class TowerOfHanoi {
    static Stack<Integer> left = new Stack<>();
    static Stack<Integer> middle = new Stack<>();
    static Stack<Integer> right = new Stack<>();
    static int total;

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter number of disks: ");
        total = input.nextInt();
        for (int i = total; i >= 1; i--) {
            left.push(i);
        }
        System.out.println("\nInitial Position:\n");
        show();
        move(total, left, right, middle, "A", "C", "B");
        input.close();
    }

    static void move(int disk, Stack<Integer> from, Stack<Integer> to,
                     Stack<Integer> helper, String start, String end, String extra) {
        if (disk == 1) {
            to.push(from.pop());
            System.out.println("Move Disk 1 from " + start + " to " + end + "\n");
            show();
            return;
        }
        move(disk - 1, from, helper, to, start, extra, end);
        to.push(from.pop());
        System.out.println("Move Disk " + disk + " from " + start + " to " + end + "\n");
        show();
        move(disk - 1, helper, to, from, extra, end, start);
    }

    static void show() {
        for (int level = total; level >= 1; level--) {
            printRod(left, level);
            printRod(middle, level);
            printRod(right, level);
            System.out.println();
        }
        for (int i = 0; i < total * 8 + 5; i++) {
            System.out.print("-");
        }
        System.out.println();
        System.out.printf("%" + total + "sA%" + (total + 7) + "sB%" + (total + 7) + "sC\n\n", "", "", "");
    }

    static void printRod(Stack<Integer> rod, int level) {
        if (rod.size() >= level) {
            int disk = rod.get(level - 1);
            int spaces = total - disk;
            for (int i = 0; i < spaces; i++)
                System.out.print(" ");
            for (int i = 0; i < disk * 2 - 1; i++)
                System.out.print("*");
            for (int i = 0; i < spaces; i++)
                System.out.print(" ");
        } else {
            for (int i = 0; i < total - 1; i++)
                System.out.print(" ");
            System.out.print("|");
            for (int i = 0; i < total - 1; i++)
                System.out.print(" ");
        }
        System.out.print("    ");
    }
}
