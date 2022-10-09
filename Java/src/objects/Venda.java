package objects;

import Interfaces.Vend;

import java.io.Serializable;
import java.util.Objects;


public class Venda implements Vend, Serializable {

    /**variaveis de instancia*/
    private Produto prd;
    private Cliente clt;
    private double preco;
    private int mes;
    private int filial;
    private String tipo;
    private int quant;

    /**construtores*/
    public Venda() {

        this.prd = new Produto();
        this.clt = new Cliente();
        this.preco = 0.0;
        this.mes = 0;
        this.filial = 0;
        this.tipo = "";
        this.quant = 0;
    }

    public Venda(Produto prd, Cliente clt, double preco, int mes, int filial, String tipo, int quant) {

        this.prd = prd.clone();
        this.clt = clt.clone();
        this.preco = preco;
        this.mes = mes;
        this.filial = filial;
        this.tipo = tipo;
        this.quant = quant;
    }

    public Venda(Venda v){

        this.prd = v.getPrd().clone();
        this.clt = v.getClt().clone();
        this.preco = v.preco;
        this.mes = v.mes;
        this.filial = v.filial;
        this.tipo = v.tipo;
        this.quant = v.quant;
    }

    /**metodos(gets/sets)*/
    public Produto getPrd() {

        return this.prd;
    }

    public void setPrd(Produto prd) {

        this.prd = prd.clone();
    }

    public Cliente getClt() {

        return this.clt;
    }

    public void setClt(Cliente clt) {

        this.clt = clt.clone();
    }

    public double getPreco() {

        return this.preco;
    }

    public void setPreco(double preco) {

        this.preco = preco;
    }

    public int getMes() {

        return this.mes;
    }

    public void setMes(int mes) {

        this.mes = mes;
    }

    public int getFilial() {

        return this.filial;
    }

    public void setFilial(int filial) {

        this.filial = filial;
    }

    public String getTipo() {

        return this.tipo;
    }

    public void setTipo(String tipo) {

        this.tipo = tipo;
    }

    public int getQuant() {

        return this.quant;
    }

    public void setQuant(int quant) {

        this.quant = quant;
    }

    /**metodo clone*/
    public Venda clone(){

        return new Venda(this);
    }

    /**metodo equals*/
    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Venda)) {
            return false;
        }
        Venda Venda = (Venda) o;
        return Objects.equals(prd, Venda.prd) && Objects.equals(clt, Venda.clt) && preco == Venda.preco && mes == Venda.mes && filial == Venda.filial && Objects.equals(tipo, Venda.tipo) && quant == Venda.quant;
    }


    /**metodo toString*/
    @Override
    public String toString() {
        return "prd=" + getPrd() +
            ", clt=" + getClt()+
            ", preco='" + getPreco() +
            ", mes='" + getMes() +
            ", filial='" + getFilial() +
            ", tipo='" + getTipo() +
            ", quant='" + getQuant();
    }

}

