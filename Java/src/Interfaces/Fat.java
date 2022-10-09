package Interfaces;

import objects.*;
import java.util.Map;
import java.util.Set;

public interface Fat {

    Set<Venda> getFaturacao();

    String getFile();

    void setFile(String file);

    int getNumVendas();

    int getVendas0();

    void setVendas0(int ven);

    void setFaturacao(Set<Venda> faturacao);

    void addVenda(Venda v);

    Set<Cliente> getBlackList();

    void setBlackList(Set<Cliente> clt);

    void addBlackList(Cliente c);

    int getVendasLidas();

    void setVendasLidas(int vendas);

    void addVendasLidas();

    int[] getTotalCompras();

    void addTotalCompras(int mes);

    double[][] getTotalFaturado();

    void addTotalFaturado(int mes,int filial,double faturado);

    int[][] getTotalClientes();

    void addTotalClientes(int mes,int filial,int num);

    int[] totalVendasClientesMes(int mes);

    int totalPrds();

    int totalClts();

    Set<Produto> getProdutos();

    Set<String> getProdutosCod();

    Set<Venda> filtraVendasCliente(String clt);

    Set<Venda> filtraVendasProduto(String prod);

    Set<AuxStruct> query6(int x);

    Map<String,Set<String>> query8();

    Map<String, AuxStruct2> query10();
}
