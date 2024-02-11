public class StackX {
    private int maxSize;
    private long[] stackArray;
    private int top;
    public StackX(int s) {
        maxSize = s;
        stackArray = new long[maxSize];
        top = -1;
    }
    public void push(long j) {
        if (isFull())
            stackArray[++top] = j;
        else
            System.out.println("Cant insert, stack is full");
    }
    public long pop() {
        return stackArray[top--];
    }
    public long peek() {
        return stackArray[top];
    }
    public boolean isEmply() {
        return (top == -1);
    }
    public boolean isFull() {
        return !(top == maxSize - 1);
    }
}