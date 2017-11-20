var duration = 0;
// Random plot generation code
function rand() {
	return Math.random();
}

Plotly.plot('myDiv', [{
	y: [1,2,3].map(rand)
}, {
	y: [1,2,3].map(rand)
}]);

var cnt = 0;

var interval = setInterval(function() {

	Plotly.extendTraces('myDiv', {
		y: [[rand()], [rand()]]
	}, [0, 1]);

	if(cnt === 100) clearInterval(interval);
}, 300);


// Progress bar movement code
function move() {
    var elem = document.getElementById("myBar");
    var width = 10;
    var id = setInterval(frame, 10);
    function frame() {
        if (width >= 100) {
            clearInterval(id);
        } else {
            width++;
            elem.style.width = width + '%';
            elem.innerHTML = width * 1 + '%';
        }
    }
}

//More Protocol stuff
var count = 0
function deleteRow(row)
{
	var i=row.parentNode.parentNode.rowIndex;
	document.getElementById('room_fileds').deleteRow(i-1);
}
function add_fields() {
	count++
	var county = count.toString();
	var objTo = document.getElementById('room_fileds')
	var divtest = document.createElement("tr");
	divtest.innerHTML = '<td style="text-align:center"><input type="color" id="color' + count + '"></td><td  style="text-align:center"><input type="number" id="time' + count + '" placeholder="1"></td><td><input type="button" id="delPOIbutton" value="Delete" onclick="deleteRow(this)"/></td>';
	objTo.appendChild(divtest)
}

arrayObject = [];
// Submit Button Post Processing
$("#subButon").on("click", function() {
	arrayObject = [];
	duration=0;
  for (var index = 0; index < count + 1; index++) {
	duration = duration + parseInt($("#time" + index).val(), 10);
      arrayObject.push({
        color: $("#color" + index).val(),
        time: $("#time" + index).val()
      })
    }
  console.log(arrayObject);
  console.log(duration);
var html = '<table id="currprot" border="1" cellpadding="0" cellspacing="0" >';
 html += '<tr>';
  html += '<th style="text-align:center">Color</th><th style="text-align:center">Time (seconds)</th>';
  html += '</tr>';
 for( var i = 0; i < arrayObject.length; i++) {
  html += '<tr>';
  for( var j in arrayObject[i] ) {
    html += '<td>' + arrayObject[i][j] + '</td>';
  }
 }
 html += '</table>';
 document.getElementById('currentProtocol').innerHTML = html;

 data = JSON.stringify(arrayObject);

 $.ajax({
 	 url: '/',
 	 type: 'POST',
 	 data: data,
 	 contentType: 'application/json;charset=UTF-8',
 	 cache:false,
 	 success: function (response) {
 			 $(".ForumTagList").html(response);    //your flask route needs to send back the html for just your list items
			  console.log(data);
 			 alert('Protocol Submitted')
 	 },
 	 error: function(response){
 			 alert('Error refreshing forum items')
 	 }
 });
arrayObject = [];
})
