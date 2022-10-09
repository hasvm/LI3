package objects;

public class AuxStruct2 implements Comparable{

        /**variaveis de instancia*/
        private double fat[][];
        private String cod;

        /**construtores*/
        public AuxStruct2(double fat, String cod,int mes,int filial) {
            this.fat = new double[12][3];
            this.fat[mes][filial] = fat;
            this.cod = cod;
        }

        public AuxStruct2() {
            this.fat = new double[12][3];
            this.cod = null;
        }

        /**metodos*/
        public double[][] getFat() {

            return fat;
        }

        public void setFat(double fat[][]) {

            this.fat = fat;
        }

        public String getCod() {

            return cod;
        }

        public void setCod(String cod) {

            this.cod = cod;
        }

        public void incFat(double fat, int mes,int filial){

            this.fat[mes][filial] += fat;
        }


        /**metodo de comparaçao*/
        @Override
        public int compareTo(Object o) {
            AuxStruct2 q = (AuxStruct2) o;
            return this.cod.compareTo(q.getCod());
        }
    }
