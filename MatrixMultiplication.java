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

import java.util.concurrent.*;
public class MatrixMultiplication {
    private double[][] a;
    private double[][] b;
    private double[][] c;
    private static int MATRIX_SIZE = 16,POOL_SIZE = Runtime.getRuntime().availableProcessors(),MIN_THRESHOLD = 64;
    
    private final ExecutorService exec = Executors.newFixedThreadPool(POOL_SIZE);
    /**
     * @param args the command line arguments
     */
    
    public MatrixMultiplication(){
        this.a = new double[MATRIX_SIZE][MATRIX_SIZE];
        this.b = new double[MATRIX_SIZE][MATRIX_SIZE];
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a.length; j++) {
                a[i][j] = 1.0;
                b[i][j] = 2.0;
            }
            
        }
        this.c = new double[MATRIX_SIZE][MATRIX_SIZE];
    }
    public void check(){
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a.length; j++) {
                System.out.print(""+c[i][j]+" ");
            }
            System.out.println("");
        }
    }
    public void multiply() {
        //multiplyRecursive(0, 0, 0, 0, 0, 0, a.length);
        Future f = exec.submit(new MultiplyTask(a, b, c, 0, 0, 0, 0, 0, 0, a.length));
        try {
            f.get();
            exec.shutdown();
        } catch (Exception e) {

        }
    }
    
    class MultiplyTask implements Runnable{
        private double[][] a;
        private double[][] b;
        private double[][] c;
        private int a_i, a_j,b_i,b_j,c_i,c_j,size;
        
        public MultiplyTask(double[][] a, double[][] b, double[][] c, int a_i,int a_j, int b_i, int b_j, int c_i, int c_j, int size){
            this.a = a;
            this.b = b;
            this.c = c;
            this.a_i = a_i;
            this.a_j = a_j;
            this.b_i = b_i;
            this.b_j = b_j;
            this.c_i = c_i;
            this.c_j = c_j;
            this.size = size;
        }

        @Override
        public void run() {
            int h = size/2;
            // does the matrix multiplication if the
            if(size <= MIN_THRESHOLD){
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        for (int k = 0; k < size; k++) {
                            c[c_i+i][c_j+j] += a[a_i+i][a_j+k] + b[b_i+k][b_j+j];
                        } 
                    }
                }
            } else {
                MultiplyTask[] mt = {
                  new MultiplyTask(a,b,c,a_i,a_j,b_i,b_j,c_i,c_j,h),
                  new MultiplyTask(a,b,c,a_i,a_j,b_i,b_j,c_i,c_j,h),
                  new MultiplyTask(a,b,c,a_i,a_j,b_i,b_j,c_i,c_j,h),
                  new MultiplyTask(a,b,c,a_i,a_j,b_i,b_j,c_i,c_j,h),  
                  new MultiplyTask(a,b,c,a_i,a_j,b_i,b_j,c_i,c_j,h),
                  new MultiplyTask(a,b,c,a_i,a_j,b_i,b_j,c_i,c_j,h)
                };
                FutureTask[] tasks = new FutureTask[mt.length/2];
                for (int i = 0; i < mt.length; i+=2) {
                    tasks[i/2] = new FutureTask((Callable) new seq(mt[i],mt[i+1]));
                    exec.execute(tasks[i/2]);
                }
                for (int i = 0; i < tasks.length; i++) {
                    tasks[i].run();
                }
                try{
                    for (int i = 0; i < tasks.length; i++) {
                        tasks[i].get();
                    }
                } catch(Exception e){
                    
                }
 
                
            }
        }
        
    }
    
    class seq implements Runnable{
        private MultiplyTask a, b;
        
        public seq(MultiplyTask a, MultiplyTask b){
            this.a=a;
            this.b=b;
        }
        @Override
        public void run() {
            a.run();
            b.run();
        }
        
    }
   
    
}
