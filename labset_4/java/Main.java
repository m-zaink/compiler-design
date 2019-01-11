import java.util.* ; 
import java.io.* ; 



class BankerAlgorithm{
    int N ;  // Processes 
    int R ; // Resource types 
    int [][] allocation ;
    int [][] max ; 
    int [][] need ;

    void getInputData(){
        Scanner scan = new Scanner(System.in) ; 
        System.out.println("Enter number of processes : "); 
        N = scan.nextInt() ; 
        System.out.println("Enter number of Resource types : ");        
        R = scan.nextInt() ; 

        allocation = new int [N][R] ; 
        max= new int [N][R] ; 
        need= new int [N][R] ; 

    }

}



class Main{


    public static void main(String[] args) {
        BankerAlgorithm algo = new BankerAlgorithm() ; 
        algo.getInputData(); 
    }
}