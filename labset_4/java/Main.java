//Author : nateshmbhat
//Program : Banker's Algorithm for Deadlock Avoidance

import java.util.*;
import java.io.*;

class BankerAlgorithm {
    int N; // Processes
    int R; // Resource types
    int[][] allocation;
    int[][] max;
    int[][] need;
    int[] available;
    boolean[] finished;
    int[] safeSequence;

    void getInputData() {
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter number of processes : ");
        N = scan.nextInt();
        System.out.println("Enter number of Resource types : ");
        R = scan.nextInt();

        allocation = new int[N][R];
        max = new int[N][R];
        need = new int[N][R];
        available = new int[R];
        finished = new boolean[N];
        safeSequence = new int[N] ; 

        System.out.println("Enter Allocation matrix : \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < R; j++) {
                allocation[i][j] = scan.nextInt();
            }
        }

        System.out.println("Enter Max matrix : \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < R; j++) {
                max[i][j] = scan.nextInt();
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }

        System.out.println("Enter Available array : \n");
        for (int i = 0; i < R; i++)
            available[i] = scan.nextInt();
    }


    int getNextProcess(int[] work , int current){
        //cicularly traverses all the processes after the currently allocated process and if need of all recourse is less that work , then returns that processs
        process:
        for(int p=((current+1)%N) ; p!=current ; p=(p+1)%N )
        {
            for(int j=0 ;j < N ; j++){
               if( finished[p] || need[p][j]>work[j]) continue process;
            }
            return p ; //return the process to be fulfilled
        }
        return -1; //no such process
    }

    boolean findSafeSequence() {
        int[] work = available;
        int safeSequencePointer =0; 
        int current = 0;
        int  n= N ; 
        while (true) {
            int next = getNextProcess(work , current); // returns -1 if no process can be executed using work
            if (next < 0) {
                for (int i = 0; i < N; i++)
                    if (finished[i] == false)
                        return false; // no process can be given its needed share
                return true; // all processes are fulfilled
            }

            current = next ;
            finished[next] = true;
            safeSequence[safeSequencePointer++]= next ; 

            for (int i = 0; i < R; i++) {
                work[i] += allocation[next][i];
            }
        }
    }

    void displaySafeSequence(){
        System.out.println("\nSafe Sequence is : \n");
        for(int i =0 ;i < N ; i++){
            System.out.print("P"+ safeSequence[i]+ " ");
        }
        System.out.println("");
    }
}


class Main {
    public static void main(String[] args) {
        BankerAlgorithm algo = new BankerAlgorithm();
        algo.getInputData();
        if(algo.findSafeSequence()){
            algo.displaySafeSequence() ; 
        }
        else{
            System.out.println("\nNo Safe sequence exits  :( ");
        }
    }
}