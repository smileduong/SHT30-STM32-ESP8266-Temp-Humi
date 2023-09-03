const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>WEBSERVER</title>
</head>

<style>

</style>

<script>

UpDateData();

function UpDateData()
{
    var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function()
  {
      if(this.readyState == 4 && this.status == 200)
        {
        var DataVDK = xhttp.responseText;
      console.log("Dữ liệu VĐK: " + DataVDK);
      JSON.parse(DataVDK);
      var DataJson = JSON.parse(DataVDK);
      
      if(DataJson.ND != null)
      {
          document.getElementById("ND").innerHTML = DataJson.ND;
      }
      if(DataJson.DA != null)
      {
          document.getElementById("DA").innerHTML = DataJson.DA;
      }
      
    }   
  };
  
  
  xhttp.open("GET", "/LoadData", true);
  xhttp.send();
  setTimeout(function(){ UpDateData() }, 1000);
}
</script>

<body>
<h1> GIÁM SÁT NHIỆT ĐỘ - ĐỘ ẨM </h1>
<h1>
Nhiệt độ:
<label id="ND">0</label>
</h1>
<h1>
Độ ẩm:
<label id="DA">0</label>
</h1>
</body>
</html>
)=====";
