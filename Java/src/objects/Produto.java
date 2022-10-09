package objects;

import Interfaces.Prd;

import java.io.Serializable;

public class Produto implements Comparable, Prd, Serializable {

    /**variaveis de instancia*/
    private String cod;

    /**construtores*/
    public Produto() {

        this.cod = "";
    }

    public Produto(String cod) {

        this.cod = cod;
    }

    public Produto(Produto p){

        this.cod = p.cod;
    }

    /**metodos(gets/sets)*/
    public String getCod() {

        return cod;
    }

    public void setCod(String cod) {

        this.cod = cod;
    }

    /**metodo de comparaçao*/
    @Override
    public int compareTo(Object o) {
        Produto a = (Produto) o;
        return this.getCod().compareTo(a.getCod());
    }

    /**metodo equals*/
    @Override
    public boolean equals(Object o) {

        if (this == o) return true;
        if (!(o instanceof Produto)) return false;
        Produto produto = (Produto) o;
        return getCod().equals(produto.getCod());
    }

    /**metodo clone*/
    public Produto clone(){

        return new Produto(this);
    }

    /**metodo toString*/
    @Override
    public String toString() {

        return "cod=" +this.cod;
    }
}
