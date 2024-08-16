package lab1Bean;

public class lab1Bean {
    private int evenNegativeSum;
    private int oddNegativeSum;
    private String numbers;
    private String errorMessage;
    
    public lab1Bean(){
        evenNegativeSum = 0;
        oddNegativeSum = 0;
        numbers = "";
        errorMessage = "";
    }

    /**
     * @return the evenNegativeSum
     */
    public int getEvenNegativeSum() {
        return evenNegativeSum;
    }

    /**
     * @return the oddNegativeSum
     */
    public int getOddNegativeSum() {
        return oddNegativeSum;
    }

    /**
     * @return the numbers
     */
    public String getNumbers() {
        return numbers;
    }

    /**
     * @return the errorMessage
     */
    public String getErrorMessage() {
        return errorMessage;
    }

    /**
     * @param evenNegativeSum the evenNegativeSum to set
     */
    public void setEvenNegativeSum(int evenNegativeSum) {
        this.evenNegativeSum = evenNegativeSum;
    }

    /**
     * @param oddNegativeSum the oddNegativeSum to set
     */
    public void setOddNegativeSum(int oddNegativeSum) {
        this.oddNegativeSum = oddNegativeSum;
    }

    /**
     * @param numbers the numbers to set
     */
    public void setNumbers(String numbers) {
        this.numbers = numbers;
    }

    /**
     * @param errorMessage the errorMessage to set
     */
    public void setErrorMessage(String errorMessage) {
        this.errorMessage = errorMessage;
    }
}
