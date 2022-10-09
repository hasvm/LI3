package objects;

import Interfaces.Fat;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class Faturacao implements Fat, Serializable {

    /**variaveis de instancia*/
    private Set<Venda> faturacao;
    private Set<Cliente> blackList;
    private int vendas0;
    private int vendasLidas;
    private int[] totalCompras;
    private double[][] totalFaturado;
    private int[][] totalClientes;
    private String file;

    /**construtores*/
    public Faturacao(){

        this.faturacao = new HashSet<>();
        this.blackList = new TreeSet<Cliente>();
        this.vendas0 = 0;
        this.vendasLidas = 0;
        this.file = "";
        this.totalCompras = new int[12];
        this.totalFaturado = new double[12][3];
        this.totalClientes = new int[12][3];
        for(int i =0;i<12;i++){
            this.totalCompras[i]=0;
            for(int j=0;j<3;j++){
                this.totalClientes[i][j]=0;
                this.totalFaturado[i][j]=0.0;
            }
        }
    }

    public Faturacao(Set<Venda> faturacao) {

        this.faturacao = faturacao.stream().map(f -> f.clone()).collect(Collectors.toCollection(HashSet::new));
    }

    public Faturacao(Faturacao fat){

        this.faturacao = fat.getCopy();
        this.blackList = fat.getBlackListCopy();
        this.vendas0 = fat.getVendas0();
        this.vendasLidas = fat.getVendasLidas();
        this.totalCompras = fat.getTotalCompras();
        this.totalFaturado = fat.getTotalFaturado();
        this.totalClientes = fat.getTotalClientes();
        this.file = fat.getFile();
    }

    /**metodos(sets/gets/adds)*/
    public String getFile(){

        return this.file;
    }

    public void setFile(String file){
        this.file = file;
    }

    public int getNumVendas(){

        return this.faturacao.size();
    }

    public int getVendas0(){

        return this.vendas0;
    }

    public void setVendas0(int ven){

        this.vendas0 = ven;
    }

    public Set<Venda> getFaturacao() {

        return faturacao;
    }

    public Set<Venda> getCopy(){

        return this.faturacao.stream().map(f -> f.clone()).collect(Collectors.toCollection(HashSet::new));
    }

    public void setFaturacao(Set<Venda> faturacao) {

        this.faturacao = faturacao.stream().map(f -> f.clone()).collect(Collectors.toCollection(HashSet::new));;
    }

    public void addVenda(Venda v){

        this.faturacao.add(v.clone());
    }
    public Set<Cliente> getBlackList(){

        return this.blackList;
    }

    public Set<Cliente> getBlackListCopy(){

        return this.blackList.stream().map(c -> c.clone()).collect(Collectors.toCollection(TreeSet::new));
    }

    public void setBlackList(Set<Cliente> clt){
        this.blackList = clt.stream().map(c -> c.clone()).collect(Collectors.toCollection(TreeSet::new));
    }

    public void addBlackList(Cliente c){
        this.blackList.add(c);
    }

    public int getVendasLidas() {

        return this.vendasLidas;
    }

    public void setVendasLidas(int vendas) {

        this.vendasLidas = vendas;
    }

    public void addVendasLidas(){
        this.vendasLidas++;
    }


    public int[] getTotalCompras(){

        return this.totalCompras;
    }

    public void addTotalCompras(int mes){

        this.totalCompras[mes]++;
    }

    public double[][] getTotalFaturado(){

       return this.totalFaturado;
    }

    public void addTotalFaturado(int mes,int filial,double faturado){

        this.totalFaturado[mes][filial] +=faturado;
    }

    public int[][] getTotalClientes(){

        return this.totalClientes;
    }

    public void addTotalClientes(int mes,int filial,int num){

        this.totalClientes[mes][filial] += num;
    }

    public int[] totalVendasClientesMes(int mes){

        Set<Venda> ret = this.faturacao.stream().filter(v -> v.getMes() == mes).collect(Collectors.toCollection(HashSet::new));
        int[] aux = new int[2];
        aux[0] = ret.size();
        aux[1] = ret.stream().map(v -> v.getClt().clone()).collect(Collectors.toCollection(TreeSet::new)).size();

        return aux;
    }

    public int totalPrds(){

        return this.faturacao.stream().map(v -> v.getPrd().getCod()).collect(Collectors.toCollection(TreeSet::new)).size();

    }

    public int totalClts(){

        return this.faturacao.stream().map(v -> v.getClt().getCod()).collect(Collectors.toCollection(TreeSet::new)).size();

    }

    public Set<Produto> getProdutos(){

        Set<Produto> ret = this.faturacao.stream().map(v -> v.getPrd().clone()).collect(Collectors.toCollection(TreeSet::new));
        return ret;
    }

    public Set<String> getProdutosCod(){

        Set<String> ret = this.faturacao.stream().map(v -> v.getPrd().getCod()).collect(Collectors.toCollection(TreeSet::new));
        return ret;
    }

    public Set<Venda> filtraVendasCliente(String clt){

        Set<Venda> ret = this.faturacao.stream().filter(v -> v.getClt().getCod().equals(clt)).map(v -> v.clone()).collect(Collectors.toCollection(HashSet::new));
        return ret;
    }

    public Set<Venda> filtraVendasProduto(String prod){

        Set<Venda> ret = this.faturacao.stream().filter(v -> v.getPrd().getCod().equals(prod)).map(v -> v.clone()).collect(Collectors.toSet());
        return ret;
    }

    public Set<String> setSetStr(String str){

        Set<String> aux = new TreeSet<String>();
        aux.add(str);
        return aux;
    }


    /**metodos das queryes*/
    public Set<AuxStruct> query6(int x){

        Map<String, AuxStruct> aux = new HashMap<String, AuxStruct>();
        Map<String,Set<String>> aux2 = new HashMap<>();

        for(Venda v : this.faturacao) {
            if (aux.containsKey(v.getPrd().getCod())) {
                aux.get(v.getPrd().getCod()).incQuant(v.getQuant());
                aux2.get(v.getPrd().getCod()).add(v.getClt().getCod());
            } else {
                aux.put(v.getPrd().getCod(), new AuxStruct(v.getQuant(),v.getPrd().getCod()));
                Set<String> aux3 = this.setSetStr(v.getClt().getCod());
                aux2.put(v.getPrd().getCod(), aux3);
            }
        }

        Set<AuxStruct> ret = aux.values().stream().sorted(AuxStruct::compareTo).limit(x).collect(Collectors.toCollection(TreeSet::new));
        Set<AuxStruct> ret2 = new TreeSet<AuxStruct>();
        for(AuxStruct q : ret){
            q.setQuant(aux2.get(q.getCod()).size());
            ret2.add(q);
        }
        return ret2;
    }


    public Map<String,Set<String>> query8(){

        Map<String,Set<String>> aux = new HashMap<>();

        for(Venda v : this.faturacao) {
            if (aux.containsKey(v.getClt().getCod())) {
                aux.get(v.getClt().getCod()).add(v.getPrd().getCod());
            } else {
                Set<String> aux3 = this.setSetStr(v.getPrd().getCod());
                aux.put(v.getClt().getCod(), aux3);
            }
        }

        return aux;
    }

    public Map<String,AuxStruct2> query10(){

        Map<String,AuxStruct2> ret = new HashMap<>();
        for(Venda v: this.faturacao){
            if(ret.containsKey(v.getPrd().getCod())){
                ret.get(v.getPrd().getCod()).incFat(v.getPreco()*v.getQuant(),v.getMes(),v.getFilial());
            }
            else{
                ret.put(v.getPrd().getCod(),new AuxStruct2(v.getPreco()*v.getQuant(),v.getPrd().getCod(),v.getMes(),v.getFilial()));
            }
        }

        return ret;
    }

    /**metodo clone*/
    public Faturacao clone(){

        return new Faturacao(this);
    }

    /**metodo equals*/
    @Override
    public boolean equals(Object o) {

        if (this == o) return true;
        if (!(o instanceof Faturacao)) return false;
        Faturacao faturacao1 = (Faturacao) o;
        return getFaturacao().equals(faturacao1.getFaturacao());
    }

    /**metodo toString*/
    @Override
    public String toString() {

       StringBuilder s = new StringBuilder();
       for(Venda v: this.faturacao){
           s.append(v.toString());
       }
       return s.toString();
    }
}
