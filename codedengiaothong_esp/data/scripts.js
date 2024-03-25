
        let btn1 = document.getElementById("button1");
        let btn2 = document.getElementById("button2");
        let btn3 = document.getElementById("button3");
        let btn4 = document.getElementById("button4");
        let bangbaocao = document.getElementById("bang");
        let trangthai = "0";
        let stt = 1;
    function doimaunen(){
        if (trangthai=="1"){
            btn1.style.backgroundColor = "green";
            btn2.style.backgroundColor = "red";
            btn3.style.backgroundColor = "red";
        }
        if (trangthai=="2"){
            btn1.style.backgroundColor = "red";
            btn2.style.backgroundColor = "green";
            btn3.style.backgroundColor = "red";
        }
        if (trangthai=="3"){
            btn1.style.backgroundColor = "red";
            btn2.style.backgroundColor = "red";
            btn3.style.backgroundColor = "green";
        }
        if (trangthai=="0") {
            btn1.style.backgroundColor = "red";
            btn2.style.backgroundColor = "red";
            btn3.style.backgroundColor = "red";
        }
    }
    function stt1(){  
    alert("Trạng thái không có luồng nào bị kẹt xe"); 
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);
      trangthai = myObj.trangthai;
      doimaunen();
    }
    }; 
    xhr.open("GET", "/trangthai1", true);
    xhr.send();     
    }  
    function stt2(){
    alert("Trạng thái luồng chính bị kẹt");
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);
      trangthai = myObj.trangthai;
      doimaunen();
    }
    }; 
    xhr.open("GET", "/trangthai2", true);
    xhr.send();  
    }
    function stt3(){
    alert("Trạng thái luồng phụ bị kẹt");
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);
      trangthai = myObj.trangthai;
      doimaunen();
    }
    }; 

    xhr.open("GET", "/trangthai3", true);
    xhr.send();  
    }   

    function baoketxe(){
        const input = prompt("Nhập vào ghi chú:");
        // alert(`Your name is ${input}`);
        const t = new Date();
        let h = dinhdang2so(t.getHours());
        let m = dinhdang2so(t.getMinutes());
        let s = dinhdang2so(t.getSeconds());
        let d = dinhdang2so(t.getDate());
        let mm = dinhdang2so(t.getMonth()+1);
        let y = dinhdang2so(t.getFullYear());
        bangbaocao.innerHTML = bangbaocao.innerHTML + "<tr><td>"+stt +"</td><td> "+h +":"+m +":"+ s+" " +d+"/"+mm+"/"+ y+"</td><td>"+input+"</td></tr>";
        stt +=1;
    }

    function hienthithoigian(){
        const t = new Date();
        let h = dinhdang2so(t.getHours());
        let m = dinhdang2so(t.getMinutes());
        let s = dinhdang2so(t.getSeconds());
        document.getElementById("thoigian").innerHTML = h +":" + m +":" +s;

        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var myObj = JSON.parse(this.responseText);
          console.log(myObj);
          let nhietdo = myObj.nhietdo;
          let doam = myObj.doam;          
        }
        }; 
        xhr.open("GET", "/dht11", true);
        xhr.send(); 
        document.getElementById("nhietdo").innerHTML = nhietdo +" °C";
        document.getElementById("doam").innerHTML = doam +" %";
        setTimeout(hienthithoigian, 1000);
    }
    function dinhdang2so(x){
        if (x<10){
            return x = "0"+x;
        }
        return x;
    }
