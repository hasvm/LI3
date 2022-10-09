package Interfaces;

import objects.*;
import java.util.*;

public interface SGV {

    CatalogoProdutos getCatProd();

    void setCatProd(CatalogoProdutos catProd);

    CatalogoClientes getCatClt();

    CatalogoClientes getCatCltCopy();

    void setCatClt(CatalogoClientes catClt);

    Faturacao getFaturacao();

    Faturacao getFaturacaoCopy();

    void setFaturacao(Faturacao fat);

    Map<Integer, Filial> getFilias();

    Map<Integer, Filial> getFiliaisCopy();

    void setFilias(Map<Integer, Filial> fil);

    void load();

    String getFile();

    int getVendasErradas();

    int totalPrds();

    int totalPrdsDifComp();

    int totalPrdsNaoComp();

    int totalClts();

    int totalCltsComp();

    int totalCltsNaoComp();

    double totalFaturado();

    int getVendas0();

    Set<String> query1();

    int[] query2(int mes);

    int[][] filtrarVendasMesFilial(int mes);

    double[][] query3(String clt);

    double[][] query4(String prod);

    Set<AuxStruct> query5(String clt);

    Set<AuxStruct> query6(int x);

    Map<Integer, Set<AuxStruct>> query7();

    Set<AuxStruct> query8(int x);

    Set<String> setSetStr(String str);

    Set<AuxStruct> query9(String str, int x);

    Set<AuxStruct2> query10();
}