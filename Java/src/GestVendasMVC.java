import objects.GestVendas;
import objects.View;

import java.io.IOException;
import java.util.Scanner;
import java.util.Set;


public class GestVendasMVC {

    /**
     * variáveis de instância
      do menu principal*/
    public static GestVendas sgv;
    public static View v;


    /**apresentação e cálcula da query 1 do menu principal*/
    public static void q1(){

        v.showMessage("Nome de ficheiro lido: "+sgv.getFile());
        v.showMessage("Número total de vendas erradas lidas: "+sgv.getVendasErradas());
        v.showMessage("Número total de produtos: "+sgv.totalPrds());
        v.showMessage("Número total de diferentes produtos comprados: "+sgv.totalPrdsDifComp());
        v.showMessage("Número total de produtos não comprados: "+sgv.totalPrdsNaoComp());
        v.showMessage("Número total de clientes: "+sgv.totalClts());
        v.showMessage("Número total de clientes que compraram: "+sgv.totalCltsComp());
        v.showMessage("Número total de clientes que não compraram: "+sgv.totalCltsNaoComp());
        v.showMessage("Número total de compras de valor total igual a 0.0: "+sgv.getVendas0());
        v.showMessage("Total faturado: "+sgv.totalFaturado());
    }

    /**apresentação e cálcula da query 2 do menu principal*/
    public static void q2(){

        int[][] totalClientes = sgv.getFaturacaoCopy().getTotalClientes();
        double[][] totalFaturado = sgv.getFaturacaoCopy().getTotalFaturado();
        int[] totalCompras = sgv.getFaturacaoCopy().getTotalCompras();
        double total = 0.0;

        for(int i=0;i<12;i++){
            v.showMessage("Mês: "+(i+1));
            v.showMessage("Número total de compras: "+totalCompras[i]);
            for(int j=0; j<3;j++){
                v.showMessage("Filial "+(j+1)+":");
                v.showMessage("Faturação total : "+totalFaturado[i][j]);
                total += totalFaturado[i][j];
                v.showMessage("Número de clientes: "+totalClientes[i][j]);
            }
            v.showMessage("Total Faturado: "+total);
            v.showMessage("----------------------------------------------");
        }
    }

    /**apresentação e cálcula da query 3 do menu principal*/
    public static void q3(){

        v.showMessage("Lista de produtos nunca comprados:");
        Set<String> aux = sgv.query1();
        v.showMessage("Número de produtos nunca comprados: "+aux.size());
        for(String s: aux){
            v.showMessage(s);
        }
    }


    /**apresentação e cálcula da query 4 do menu principal*/
    public static void q4(){
        int mes;

        Scanner m = new Scanner(System.in);
        v.showMessage("Filial prima 0.");
        v.showMessage("Total prima 1.");
        int x = m.nextInt();
        do {
            v.showMessage("Insira o mes pretendido.");
            mes = m.nextInt();
            v.showMessage("");
            if (mes <= 12 && mes >= 1) {
                if(x>0) {
                    int[] aux = sgv.query2(mes-1);
                    v.showMessage("Total de vendas: " + aux[0]);
                    v.showMessage("Número de clientes distintos: " + aux[1]);
                }
                else {
                    int[][] aux = sgv.filtrarVendasMesFilial(mes);
                    for(int i=0;i<3;i++){
                        v.showMessage("Filial "+(i+1)+":");
                        v.showMessage("Total de vendas: " + aux[i][0]);
                        v.showMessage("Número de clientes distintos: " + aux[i][1]);
                    }
                }
            }
            else v.showMessage("Mes invalido." +
                    "Deve inserir um valor entre 1 e 12.");
        } while (mes > 12 || mes < 1);
    }

    /**apresentação e cálcula da query 5 do menu principal*/
    public static void q5(){

        String codCliente;
        double[][] aux;
        Scanner codC =  new Scanner(System.in);
        do{
            v.showMessage("Insira o codigo cliente:");
            codCliente = codC.next();
            v.showMessage("");
            if (codCliente.length() == 5){
                aux = sgv.query3(codCliente);
                for(int i=0;i<12;i++) {
                    v.showMessage("Mês "+(i+1)+": ");
                    v.showMessage("Compras: "+(int) aux[i][0]);
                    v.showMessage("Produtos distintos: "+(int) aux[i][1]);
                    v.showMessage("Valor Total: "+aux[i][2]);
                }
            }
            else v.showMessage("Codigo invalido." +
                    "O codigo deve ter um comprimento de 5 caracteres.");
        } while (codCliente.length() != 5);
    }

    /**apresentação e cálcula da query 6 do menu principal*/
    public static void q6(){

        double[][] aux = new double[12][3];
        String codProduto;
        Scanner codP = new Scanner(System.in);
        do{
            v.showMessage("Insira o codigo do produto:");
            codProduto = codP.next();
            v.showMessage("");
            if (codProduto.length() == 6){
                aux = sgv.query4(codProduto);
                for(int i=0;i<12;i++) {
                    v.showMessage("Mês "+(i+1)+": ");
                    v.showMessage("Comprado: "+(int) aux[i][0]);
                    v.showMessage("Clientes que compraram: "+(int) aux[i][1]);
                    v.showMessage("Valor Total: "+aux[i][2]);
                }
            }
            else v.showMessage("Codigo invalido." +
                    "O codigo deve ter um comprimento de 6 caracteres.");
        } while (codProduto.length() != 6);
    }

    /**apresentação e cálcula da query 7 do menu principal*/
    public static void q7(){

        String codCliente;
        Scanner codC =  new Scanner(System.in);
        do{
            v.showMessage("Insira o codigo cliente:");
            codCliente = codC.next();
            v.showMessage("");
            if (codCliente.length() == 5){
                v.showMessage("Proutos mais comprados e a sua quantidade: ");
                v.showSet(sgv.query5(codCliente));
            }
            else v.showMessage("Codigo invalido." +
                    "O codigo deve ter um comprimento de 5 caracteres.");
        } while (codCliente.length() != 5);
    }

    /**apresentação e cálcula da query 8 do menu principal*/
    public static void q8(){


        int top;
        Scanner t = new Scanner(System.in);
        v.showMessage("Insira o top de produtos mais vendidos, que deseja visializar:");
        top = t.nextInt();
        v.showMessage("Os "+top+"vendidos e o número de clts distintos: ");
        v.showSet(sgv.query6(top));
    }

    /**apresentação e cálcula da query 9 do menu principal*/
    public static void q9(){

        v.showMap(sgv.query7());
    }

    /**apresentação e cálcula da query 10 do menu principal*/
    public static void q10(){
        int top;
        Scanner t = new Scanner(System.in);
        v.showMessage("Insira o top de clientes, que compraram mais produtos diferentes, que deseja visializar:");
        top = t.nextInt();
        v.showSet(sgv.query8(top));
    }

    /**apresentação e cálcula da query 11 do menu principal*/
    public static void q11(){
        String codProduto;
        int top;
        Scanner codP = new Scanner(System.in);
        Scanner t = new Scanner(System.in);
        do{
            v.showMessage("Insira o codigo do produto:");
            codProduto = codP.next();
            v.showMessage("");
            if (codProduto.length() == 6){
                v.showMessage("Insira o top de clientes, que mais compraram o produto, que deseja visializar:");
                top = t.nextInt();
                v.showMessage("" +
                        "");
                v.showSet(sgv.query9(codProduto,top));
            }
            else v.showMessage("Codigo invalido." +
                    "O codigo deve ter um comprimento de 6 caracteres.");
        } while (codProduto.length() != 6);
    }

    /**apresentação e cálcula da query 12 do menu principal*/
    public static void q12(){
        v.showSEt2(sgv.query10());

    }

    public static void main(String[] args) throws InterruptedException, IOException {

        sgv = new GestVendas();
        v = new View();
        sgv.load();
        Scanner sc = new Scanner(System.in);
        int val;
        do {
            v.menu();
            val = sc.nextInt();
            switch (val) {
                case 1:
                    q1();
                    break;

                case 2:
                    q2();
                    break;

                case 3:
                    q3();
                    break;

                case 4:
                    q4();
                    break;

                case 5:
                    q5();
                    break;

                case 6:
                    q6();
                    break;

                case 7:
                    q7();
                    break;

                case 8:
                    q8();
                    break;

                case 9:
                    q9();
                    break;

                case 10:
                    q10();
                    break;

                case 11:
                    q11();
                    break;

                case 12:
                    q12();
                    break;

                case 13:
                    sgv.WriteObjectToFile();
                    break;

                case 14:
                    sgv = new GestVendas();
                    sgv.LoadObjectToFile();
            }
        }while (val != 0) ;
    }
}