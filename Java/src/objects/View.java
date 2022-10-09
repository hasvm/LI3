package objects;

import java.util.*;

public class View {

    /**
     * Classe para apresentação dos resultados
     */


    /**apresentação dos dados num set de auxstruct*/
    public static void showSet(Set<AuxStruct> res){
        int flag =1;
        int count =0;
        Scanner sc = new Scanner(System.in);
        Iterator<AuxStruct> it = res.iterator();
        do {
                if(it.hasNext()){
                AuxStruct q = it.next();
                System.out.println(q.getCod() + " : " + q.getQuant());
                count++;
                if (count == 12) {
                    count = 0;
                    System.out.println("Para ver próximo produto prima: 1");
                    System.out.println("Para Voltar ao menu anterior: 0");
                    flag = sc.nextInt();
                }
            } else flag=0;
        }while(flag==1);
        System.out.println("Insira char para continuar");
        sc.next();
    }

    /**apresentação dos dados num set de auxstruct2*/
    public static void showSEt2(Set<AuxStruct2> res){
        int flag =1;
        Scanner sc = new Scanner(System.in);
        Iterator<AuxStruct2> it = res.iterator();
        do {
            for(int k =0;k<res.size()-1 && flag==1;k++) {
                AuxStruct2 q = it.next();
                System.out.println(q.getCod());
                for (int i = 0; i < 12; i++) {
                    System.out.println("Mês: " + (i + 1));
                    for (int j = 0; j < 3; j++) {
                        System.out.println("Filial: " + (j + 1));
                        System.out.println("Faturado: " + q.getFat()[i][j]);
                    }
                }
                System.out.println("Para ver próximo produto prima: 1");
                System.out.println("Para Voltar ao menu anterior: 0");
                flag = sc.nextInt();
            }
        }while(flag==1);
        System.out.println("Insira char para continuar");
        sc.next();
    }

    /**apresentação dos dados num map com sets auxstruct*/
    public static void showMap(Map<Integer, Set<AuxStruct>> res){
        for(int i=0;i<3;i++){
            System.out.println("Filial: "+(i+1));
            showSet(res.get(i));
        }
    }

    /**apresentação de uma simples string*/
    public static void showMessage(String str){

        System.out.println(str);
    }

    /**menu principal*/
    public static void menu() {

        System.out.print("Opcoes validas:\n" +
                "0 - Sair do programa.\n\n" +
                "Consultas estatisticas:\n" +
                "1 - Apresenta os dados referentes ao ultimo ficheiro de vendas lido.\n" +
                "2 - Apresenta os numeros gerais dos dados atuais ja registados nas estruturas.\n\n" +
                "Consultas interativas:\n" +
                "3 - Lista, ordenada alfabeticamente, com os codigos dos produtos nunca comprados e o seu total.\n" +
                "4 - Determina o numero total global de vendas realizadas e o numero total de clientes que as fizeram.\n" +
                "5 - Determina, para cada mes, quantas compras um cliente fez, quantos produtos diferentes comprou e quanto gastou no total.\n" +
                "6 - Determina, mes a mes, quantas vezes um produto foi comprado, por quantos clientes e o total faturado.\n" +
                "7 - Determina, por ordem decrescente de quantidade, a lista de codigos de produtos que um cliente mais comprou e quantos.\n" +
                "8 - Determina o conjunto dos X produtos mais vendidos em todo o ano e indica o numero total de clientes que o compraram.\n" +
                "9 - Determina, para cada filial, a lista dos 3 maiores compradores em termos de dinheiro faturado.\n" +
                "10 - Determina os codigos dos X clientes que compraram mais produtos diferentes, indicando quantos, por ordem decrescente do numero de produtos.\n" +
                "11 - Determina o conjuntos dos X clientes que mais compraram um produto e para cada um qual o valor gasto.\n" +
                "12 - Determina, mes a mes, a faturacao total de cada produto.\n" +
                "13 - Salvar dados em ficheiro dat.\n" +
                "14 - Ler dados em ficheiro dat.\n\n" +
                "Insira o numero do comando que pretende:\n");
    }
}