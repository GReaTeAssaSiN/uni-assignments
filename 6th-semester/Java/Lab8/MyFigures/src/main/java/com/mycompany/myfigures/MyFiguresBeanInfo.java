package com.mycompany.myfigures;

import java.beans.*;

public class MyFiguresBeanInfo extends SimpleBeanInfo {
    public PropertyDescriptor[] getPropertyDescriptors() {
        try {
        PropertyDescriptor rectangular = new PropertyDescriptor("rectangular", MyFigures.class);
        PropertyDescriptor pd[] = {rectangular};
        return pd;
        }
        catch(Exception e) {System.out.println("Возникло исключение: " + e);}
        return null;
    }
    public static void main(String[] args){
        MyFiguresBeanInfo mf = new MyFiguresBeanInfo();
        mf.getPropertyDescriptors();
    }
}/*Возникло исключение: java.beans.IntrospectionException: Method not found:
isRectangular*/