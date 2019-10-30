/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package matrixmultiplication;

/**
 *
 * @author dishantpatel
 */
public class Test {
    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        MatrixMultiplication mm = new MatrixMultiplication();
        mm.multiply();
        long finish = System.currentTimeMillis();
        System.out.println("finished.");
        System.out.format("Time elapsed: %d ms\n", finish-start);
        mm.check();
        double c[][] = new double[16][16];
        double a[][] = new double[16][16];
        double b[][] = new double[16][16];
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a.length; j++) {
                a[i][j] = 1.0;
                b[i][j] = 2.0;
            } 
        }
        start = System.currentTimeMillis();
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                for (int k = 0; k < 16; k++) {
                     c[i][j] += a[i][k] + b[k][j];
                }
            }
        }
        finish = System.currentTimeMillis();
        System.out.println("finished.");
        System.out.format("Time elapsed: %d ms\n", finish-start);
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                System.out.print(""+c[i][j]+" ");
            }
            System.out.println("");
        }
    }
}
