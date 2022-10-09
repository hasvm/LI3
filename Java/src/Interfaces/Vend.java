package Interfaces;

import objects.Cliente;
import objects.Produto;

public interface Vend {

    Produto getPrd();

    void setPrd(Produto prd);

    Cliente getClt();

    void setClt(Cliente clt);

    double getPreco();

    void setPreco(double preco);

    int getMes();

    void setMes(int mes);

    int getFilial();

    void setFilial(int filial);

    String getTipo();

    void setTipo(String tipo);

    int getQuant();

    void setQuant(int quant);
}
