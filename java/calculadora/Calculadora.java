

import java.util.Scanner;
public class Calculadora {

    /**
     * @param args the command line arguments
     */
      public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n1 = scanner.nextInt();
        int n2 = scanner.nextInt();

        System.out.println("Ingrese un numero entero: ");
        System.out.println("Ingrese otro numero entero: ");
        System.out.println("La suma de los numeros es: " + (n1 + n2));
        System.out.println("La resta de los numeros es: " + (n1 - n2));
        System.out.println("La multiplicacion de los numeros es: " + (n1 * n2));
        if (n2 != 0) {
            System.out.println("La division de los numeros es: " + (n1 / n2));
        } else {
            System.out.println("No se puede dividir por cero");
        }
    }
}
