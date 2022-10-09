package objects;

import Interfaces.ReadData;
import Interfaces.SGV;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;


/**
 * Classe GestVendas
 */
public class GestVendas implements SGV, ReadData, Serializable {

/**Variáveis de instância*/

    private CatalogoProdutos catProd;
    private CatalogoClientes catClt;
    private Faturacao faturacao;
    private Map<Integer,Filial> filias;

/** Construtores*/

    public GestVendas() {
        this.catProd = new CatalogoProdutos();
        this.catClt = new CatalogoClientes();
        this.faturacao = new Faturacao();

        this.filias = new HashMap<Integer, Filial>();
        for(int i=0;i<3;i++)
            this.filias.put(i,new Filial());

    }

    public GestVendas(GestVendas sgv){
        this.catProd = sgv.getCatProdCopy();
        this.catClt = sgv.getCatCltCopy();
        this.faturacao = sgv.getFaturacaoCopy();
        this.filias = sgv.getFiliaisCopy();
    }

    /**devolve cátologo de produtos*/
    public CatalogoProdutos getCatProd() {

        return this.catProd;
    }

    /**devolve uma cópia do catálogo de produtos*/
    public CatalogoProdutos getCatProdCopy(){
        return this.catProd.clone();
    }

    /**determina o catálogo de produtos*/
    public void setCatProd(CatalogoProdutos catProd) {

        this.catProd = new CatalogoProdutos(catProd);
    }

    /**devolve catálogo de clientes*/
    public CatalogoClientes getCatClt() {

        return this.catClt;
    }

    /**devolve uma cópia do catálogo de clientes*/
    public CatalogoClientes getCatCltCopy(){

        return this.catClt.clone();
    }

    /**determina o catálogo de produtos*/
    public void setCatClt(CatalogoClientes catClt) {

        this.catClt = new CatalogoClientes(catClt);
    }

    /**devolve faturação*/
    public Faturacao getFaturacao() {

        return this.faturacao;
    }

    /**devolve uma cópia da faturação*/
    public Faturacao getFaturacaoCopy(){

        return this.faturacao.clone();
    }

    /**determina faturação*/
    public void setFaturacao(Faturacao fat){

        this.faturacao = new Faturacao(fat);
    }

    /**devolve filiais*/
    public Map<Integer,Filial> getFilias(){

        return this.filias;
    }

    /**devolve cópia de filiais*/
    public Map<Integer,Filial> getFiliaisCopy(){

        Map<Integer,Filial> aux = new HashMap<>();
        for(int i=0;i<3;i++){
            aux.put(i,this.getFilias().get(i).clone());
        }
        return aux;
    }

    /**determina as filias*/
    public void setFilias(Map<Integer,Filial> fil){

        this.filias = new HashMap<>();
        int i=0;
        for(Filial f :fil.values()){
            this.filias.put(i,f.clone());
            i++;
        }
    }

    /**Leitura do catálogo de produtos com Files*/
    public void readCatProd(){

        Path p = Paths.get("C:/**Users/A542/Documents/GitHub/LI3/Java/Produtos.txt");
        try{
            String aux;
            List<String> l = Files.readAllLines(p);
            int num;
            for(String s : l){
                aux = null;
                if(s.length()==6) {
                    if (s.charAt(0) >= 'A' && s.charAt(0) <= 'Z' && s.charAt(1) >= 'A' && s.charAt(1) <= 'Z'){
                        aux = s.substring(2, 6);
                        num = Integer.parseInt(aux);
                        if(num>=1000 && num<=9999){
                            this.getCatProd().addProduto(new Produto(s));
                        }
                    }
                }
            }

        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /**Leitura do catálogo de clientes com Files*/
    public void readCatClt(){

        Path p = Paths.get("C:/**Users/A542/Documents/GitHub/LI3/Java/Clientes.txt");
        try{
            List<String> l = Files.readAllLines(p);
            String aux;
            int num;
            for(String s : l) {
                aux = null;
                if(s.length()==5) {
                    if (s.charAt(0) >= 'A' && s.charAt(0) <= 'Z') {
                        aux = s.substring(1, 5);
                        num = Integer.parseInt(aux);
                        if (num >= 1000 && num <= 5000) {
                            this.getCatClt().addCliente(new Cliente(s));
                        }
                    }
                }
            }

        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /**funcção auxiliar para inicializar estrutura auxiliar no método leitura de vendas*/
    public Map<Integer,Set<String>> extra() {
        Map<Integer, Set<String>> aux = new HashMap<Integer, Set<String>>();
        for(int i=0;i<3;i++){
            aux.put(i,new HashSet<String>());
        }
        return aux;
    }


    /**Leitura das Vendas utilizando Files*/
    public void readCatVendas(){

        Path p = Paths.get("C:/**Users/A542/Documents/GitHub/LI3/Java/Vendas_1M.txt");
        String file = "Vendas_1M.txt";
        this.faturacao.setFile(file);
        try{
            List<String> l = Files.readAllLines(p);
            int i=0;
            int num,quant,mes,filial;

            double preco;
            String tipo;
            Map<Integer,Map<Integer,Set<String>>> aux2 = new HashMap<Integer,Map<Integer,Set<String>>>();
              for(int k=0;k<12;k++){
                aux2.put(k,this.extra());
            }
            for(String s : l){
                String[] fl = s.split(" ");
                i++;
                if(fl.length == 7){
                    Produto prod = new Produto(fl[0]);
                if(this.catProd.exists(prod)){
                        Cliente c = new Cliente(fl[4]);
                        if(this.catClt.exists(c)) {
                            preco = Double.parseDouble(fl[1]);
                            if (preco >= 0.0 && preco <= 999.99) {
                                quant = Integer.parseInt(fl[2]);
                                if (quant > 0 && quant <= 200) {
                                    tipo = fl[3];
                                    if (tipo.compareTo("P") == 0 || tipo.compareTo("N") == 0) {
                                        mes = Integer.parseInt(fl[5]);
                                        if (mes >= 0 && mes <= 12) {
                                            mes--;
                                            filial = Integer.parseInt(fl[6]);
                                            if(filial>=0 && filial<=3){
                                                filial--;
                                                this.filias.get(filial).addVenda(new Venda(prod,c,preco,mes,filial+1,tipo,quant));
                                                this.faturacao.addVenda(new Venda(prod,c,preco,mes,filial,tipo,quant));
                                                this.faturacao.addBlackList(c);
                                                this.faturacao.addTotalCompras(mes);
                                                this.faturacao.addTotalFaturado(mes,filial,preco*quant);
                                                aux2.get(mes).get(filial).add(s);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for(int k=0;k<12;k++) {
                for (int j = 0; j < 3; j++) {
                    this.faturacao.addTotalClientes(k,j,aux2.get(k).get(j).size());
                }
            }
            this.faturacao.setVendasLidas(i);

        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /**função que carrega sistema*/
    public void load(){

        this.readCatProd();
        this.readCatClt();
        this.readCatVendBuff();
    }

    /**Leitura das Vendas com Buffer*/
    public void readCatVendBuff(){

        try{

            FileReader fr = new FileReader("C:/**Users/A542/Documents/GitHub/LI3/Java/Vendas_1M.txt");
            BufferedReader bf = new BufferedReader(fr);
            Integer i=0;
            int z=0;
            int num,quant,mes,filial;
            double preco;
            String tipo;
            Map<Integer,Map<Integer,Set<String>>> aux2 = new HashMap<Integer,Map<Integer,Set<String>>>();
            for(int k=0;k<12;k++){
                aux2.put(k,this.extra());
            }
            String s;
           while((s = bf.readLine())!=null){
               i++;
                String[] fl = s.split(" ");
                if(fl.length == 7){
                    Produto prod = new Produto(fl[0]);
                    if(this.catProd.exists(prod)){
                        Cliente c = new Cliente(fl[4]);
                        if(this.catClt.exists(c)) {
                            preco = Double.parseDouble(fl[1]);
                            if (preco >= 0.0 && preco <= 999.99) {
                                quant = Integer.parseInt(fl[2]);
                                if (quant > 0 && quant <= 200) {
                                    tipo = fl[3];
                                    if (tipo.compareTo("P") == 0 || tipo.compareTo("N") == 0) {
                                        mes = Integer.parseInt(fl[5]);
                                        if (mes >= 0 && mes <= 12) {
                                            mes--;
                                            filial = Integer.parseInt(fl[6]);
                                            if(filial>=0 && filial<=3){
                                                filial--;
                                                this.filias.get(filial).addVenda(new Venda(prod,c,preco,mes,filial+1,tipo,quant));
                                                this.faturacao.addVenda(new Venda(prod,c,preco,mes,filial,tipo,quant));
                                                this.faturacao.addBlackList(c);
                                                this.faturacao.addTotalCompras(mes);
                                                this.faturacao.addTotalFaturado(mes,filial,preco*quant);
                                                aux2.get(mes).get(filial).add(s);
                                                if(preco==0.0) z++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            this.faturacao.setVendasLidas(i);
           this.faturacao.setVendas0(z);
            for(int k=0;k<12;k++) {
                for (int j = 0; j < 3; j++) {
                    this.faturacao.addTotalClientes(k,j,aux2.get(k).get(j).size());
                }
            }

        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /** devolve o nome do ficheiro lido*/
    public String getFile(){

        return this.faturacao.getFile();
    }

    /**devolve o número de vendas erradas*/
    public int getVendasErradas(){

        int ret = this.faturacao.getVendasLidas();
        return ret-this.faturacao.getNumVendas();
    }

    /**devolve o total de produtos comprados*/
    public int totalPrds(){

        return this.catProd.totalPrds();
    }

    /**devolve o total de produtos distintos comprados*/
    public int totalPrdsDifComp(){

        return this.faturacao.totalPrds();
    }

    /**devolve o total de produtos não comprados*/
    public int totalPrdsNaoComp(){

        return this.catProd.totalPrds()-this.faturacao.totalPrds();
    }

    /**devolve o total de clientes*/
    public int totalClts(){

        return this.catClt.totalClts();
    }

    /**devolve total de clientes distintos que compraram*/
    public int totalCltsComp(){

        return this.faturacao.totalClts();
    }

    /**devolve total de clientes que não compraram*/
    public int totalCltsNaoComp(){

        return this.totalClts()-this.totalCltsComp();
    }

    /**devolve o total faturado*/
    public double totalFaturado(){
        double[][] fat = new double[12][3];
        fat = this.faturacao.getTotalFaturado();
        double total = 0.0;
        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++) {
                total += fat[i][j];
            }
        }
        return total;
    }

    /**devolve o total de vendas com o valor 0.0*/
    public int getVendas0(){
        return this.faturacao.getVendas0();
    }

/**query1*/

    public Set<String> query1(){

        Set<String> ret = this.faturacao.getProdutosCod();
        Set<String> aux = this.catProd.getCatCodCopy();
        aux.removeAll(ret);
        return aux;
    }

/**query 2 total*/

    public int[] query2(int mes){

        int[] aux = new int[2];
        aux = this.faturacao.totalVendasClientesMes(mes);
        return aux;
    }

/**query 2 filiais*/

    public int[][] filtrarVendasMesFilial(int mes){

        int[][] aux = new int[3][2];
       for(int i=0;i<3;i++){
           Set<Venda> ret = this.filias.get(i).filtrarVendasMes(mes);
           aux[i][0] = ret.size();
           aux[i][1] = ret.stream().map(v->v.getClt()).collect(Collectors.toCollection(TreeSet::new)).size();
       }
       return aux;
    }


/**query 3*/

    public double[][] query3(String clt){

        double[][] ret = new double[12][3];
        Map<Integer,Set<Produto>> aux2 = new HashMap<Integer,Set<Produto>>();
        for(int i =0; i<12;i++) {
            ret[i][0] = 0;
            ret[i][1] = 0;
            ret[i][2] = 0.0;
            aux2.put(i,new HashSet<Produto>());
        }

        Set<Venda> aux = this.faturacao.filtraVendasCliente(clt);

        for(Venda v : aux){
            ret[v.getMes()][0]++;
            ret[v.getMes()][2] += v.getPreco()*v.getQuant();
            aux2.get(v.getMes()).add(v.getPrd());
        }

        for(int i=0; i<12; i++){
            ret[i][1] = aux2.get(i).size();
        }
        return ret;
    }

/**qyery4*/

    public double[][] query4(String prod){

        double[][] ret = new double[12][3];
        Map<Integer,Set<Cliente>> aux2 = new HashMap<Integer,Set<Cliente>>();
        for(int i =0; i<12;i++) {
            ret[i][0] = 0;
            ret[i][1] = 0;
            ret[i][2] = 0.0;
            aux2.put(i,new HashSet<Cliente>());
        }

        Set<Venda> aux = this.faturacao.filtraVendasProduto(prod);

        for(Venda v : aux){
            ret[v.getMes()][0]++;
            ret[v.getMes()][2] += v.getPreco()*v.getQuant();
            aux2.get(v.getMes()).add(v.getClt().clone());
        }

        for(int i=0; i<12; i++){
            ret[i][1] = aux2.get(i).size();
        }
        return ret;
    }


/**query 5*/

    public Set<AuxStruct> query5(String clt){

        Set<Venda> aux = this.faturacao.filtraVendasCliente(clt);
        Map<String, AuxStruct> ret = new HashMap<String, AuxStruct>();

        for(Venda v : aux){
            if(ret.containsKey(v.getPrd().getCod())){
                ret.get(v.getPrd().getCod()).incQuant(v.getQuant());
            }
            else {
                ret.put(v.getPrd().getCod(),new AuxStruct(v.getQuant(),v.getPrd().getCod()));
            }
        }

        Set<AuxStruct> aux2 = new TreeSet<AuxStruct>();
        aux2.addAll(ret.values());
        return aux2;
    }

/**query 6*/

    public Set<AuxStruct> query6(int x){

        Set<AuxStruct> ret = this.faturacao.query6(x);
        return ret;
    }

/**query7*/

    public Map<Integer, Set<AuxStruct>> query7(){

        Map<Integer, Set<AuxStruct>> aux = new HashMap<Integer, Set<AuxStruct>>();

        for(int i =0;i<3;i++){
            aux.put(i,this.filias.get(i).query7());
        }
        return aux;
    }

/**query8*/

    public Set<AuxStruct> query8(int x){

        Map<String,Set<String>> aux = new HashMap<>();

        aux = this.faturacao.query8();

        Set<AuxStruct> ret = new TreeSet<>();
        for(String str : aux.keySet()) {
            ret.add(new AuxStruct(aux.get(str).size(),str));
        }

        ret = ret.stream().limit(x).collect(Collectors.toCollection(TreeSet::new));
        return ret;
    }

/**query9*/

    public Set<String> setSetStr(String str){

        Set<String> aux = new TreeSet<String>();
        aux.add(str);
        return aux;
    }

    public Set<AuxStruct> query9(String str, int x){

        Set<Venda> aux = this.faturacao.filtraVendasProduto(str);
        Map<String, AuxStruct> aux2 = new HashMap<>();

        for(Venda v : aux) {
            if (aux2.containsKey(v.getClt().getCod())) {
                aux2.get(v.getClt().getCod()).incQuant(v.getQuant()*v.getPreco());
            } else {
                Set<String> aux3 = this.setSetStr(v.getPrd().getCod());
                aux2.put(v.getClt().getCod(), new AuxStruct(v.getQuant()*v.getPreco(),v.getClt().getCod()));
            }
        }

        Set<AuxStruct> ret = aux2.values().stream().limit(x).collect(Collectors.toCollection(TreeSet::new));
        return ret;
    }

/**query10*/

    public Set<AuxStruct2> query10() {

        Map<String,AuxStruct2> aux = new HashMap<>();
        aux = this.faturacao.query10();
        Set<AuxStruct2> ret = aux.values().stream().collect(Collectors.toCollection(TreeSet::new));
        return ret;
    }


/**método que devolve a string do objeto*/

    public String toString(){
        StringBuilder s = new StringBuilder();
        s.append("Clientes{\n");
            s.append(this.catClt.toString());
            s.append("\n");
        s.append("}\n");
        s.append("Produtos{\n");
        s.append(this.catProd.toString());
        s.append("}\n");
        s.append("Faturacao{\n");
        s.append(this.faturacao.toString());
        s.append("}\n");
        s.append("Filiais{\n");
        for(int i=0;i<3;i++){
            s.append(this.filias.get(i).toString());
        }
        s.append("}");

        return s.toString();
    }

    /**escreve objetos para ficheiro*/
    public void WriteObjectToFile() {

        try {
            String filepath = "Clientes.dat";
            FileOutputStream fileOut = new FileOutputStream(filepath);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(this.catClt);
            objectOut.close();
            filepath = "Produtos.dat";
            fileOut = new FileOutputStream(filepath);
            objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(this.catProd);
            objectOut.close();
            filepath = "Faturacao.dat";
            fileOut = new FileOutputStream(filepath);
            objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(this.faturacao);
            objectOut.close();
            filepath = "Filial.dat";
            fileOut = new FileOutputStream(filepath);
            objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(this.filias);
            objectOut.close();
            System.out.println("The Object  was succesfully written to a file");

        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    /**carrega sistema com ficheiro de objetos*/
    public void LoadObjectToFile() {

        try {
            String filepath = "C:/**Users/A542/Documents/GitHub/LI3/Java/Clientes.dat";
            FileInputStream fileIn = new FileInputStream(filepath);
            ObjectInputStream objectIn = new ObjectInputStream(fileIn);
            this.catClt = (CatalogoClientes) objectIn.readObject();
            objectIn.close();
            filepath = "C:/**Users/A542/Documents/GitHub/LI3/Java/Produtos.dat";
            fileIn = new FileInputStream(filepath);
            objectIn = new ObjectInputStream(fileIn);
            this.catProd = (CatalogoProdutos) objectIn.readObject();
            objectIn.close();
            filepath = "C:/**Users/A542/Documents/GitHub/LI3/Java/Faturacao.dat";
            fileIn = new FileInputStream(filepath);
            objectIn = new ObjectInputStream(fileIn);
            this.faturacao = (Faturacao) objectIn.readObject();
            objectIn.close();
            filepath = "C:/**Users/A542/Documents/GitHub/LI3/Java/Filial.dat";
            fileIn = new FileInputStream(filepath);
            objectIn = new ObjectInputStream(fileIn);
            this.filias = (Map<Integer, Filial>) objectIn.readObject();
            objectIn.close();

            System.out.println("The Object has been read from the file");


        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}