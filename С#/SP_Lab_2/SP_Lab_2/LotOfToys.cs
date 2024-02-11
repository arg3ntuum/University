﻿using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace SP_Lab_2{
    public class LotOfToys : Toy
    {
        public Date Date { get; private set; }
        public int Name { get; private set; }
        public int Count { get; private set; }
        public LotOfToys(int Name, int Count, Date Date, string NameProduct, string NameOfCompany, Classification Classification)
            : base(NameProduct, NameOfCompany, Classification) {
            this.Name = Name;
            this.Count = Count;
            this.Date = Date;
        }
        public LotOfToys() : base() {
            this.Name = 0;
            this.Count = 0;
            this.Date = new Date();
        }
        public void AddCounts(int value) =>
            Count += value;
    }
}