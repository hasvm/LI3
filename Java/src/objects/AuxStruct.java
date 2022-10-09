package objects;

public class AuxStruct implements Comparable{

    /**variavies de instancia*/
    private double quant;
    private String cod;

    /**construtores*/
    public AuxStruct(double quant, String cod) {
        this.quant = quant;
        this.cod = cod;
    }

    public AuxStruct() {
        this.quant = 0;
        this.cod = null;
    }

    /**metodos*/
    public double getQuant() {

        return quant;
    }

    public void setQuant(int quant) {

        this.quant = quant;
    }

    public String getCod() {

        return cod;
    }

    public void setCod(String cod) {

        this.cod = cod;
    }

    public void incQuant(double quant){

        this.quant += quant;
    }

    /**metodo de comparaçao*/
    @Override
    public int compareTo(Object o) {
        AuxStruct q = (AuxStruct) o;
        if(this.getQuant()<q.getQuant()) return 1;
        if(this.getQuant()>q.getQuant()) return -1;
        if(this.getQuant()==q.getQuant()){
            if(this.getCod().compareTo(q.getCod())<0) return -1;
            if(this.getCod().compareTo(q.getCod())>0) return 1;
        }
        if(this.getCod().compareTo(q.getCod())==0 && this.getQuant()==q.getQuant()) return 0;
        return -1;

    }
}
