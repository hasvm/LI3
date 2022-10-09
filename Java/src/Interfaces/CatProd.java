package Interfaces;

import objects.Produto;
import java.util.Set;


public interface CatProd {

    Set<Produto> getCatP();

    void setCatP(Set<Produto> catP);

    void addProduto(Produto p);

    boolean exists(Produto p);

    int totalPrds();

}
