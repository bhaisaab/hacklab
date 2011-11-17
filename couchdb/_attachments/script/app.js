$db = $.couch.db("addressbook");

function refreshAddressbook(){
  $("div#addressbook").empty();
  $db.view("addressbook/phonenumbers", {
    success: function(data){
      for (i in data.rows) {
        id = data.rows[i].id;
        name = data.rows[i].key;
        phonenumber = data.rows[i].value;
        html = '<div class="address">' +
        '<span class="name">' + name + '</span>&nbsp;' + 
        '<span class="phonenumber">' + phonenumber + '</span>&nbsp; ' +
        '<a bitly="BITLY_PROCESSED" href="#" id="' + id + '" class="edit">edit</a>&nbsp;|&nbsp;' +
        '<a bitly="BITLY_PROCESSED" href="#" id="' + id + '" class="delete">delete</a>' +
        '</div>';
        $("div#addressbook").append(html);
      }
    }
  });
}

function addUpdateForm(target, existingDoc) {
	html = '<form name="update" id="update" action=""><table>' +
		'<tr><td>Name</td><td>Number</td></tr>' +
		'<tr>' + 
			'<td><input type="text" name="name" id="name" value="' + 
			(existingDoc ? existingDoc.name : "" ) + '"></td>' + 
			'<td><input type="text" name="mobile" id="mobile" value="' + 
			(existingDoc ? existingDoc.mobile : "") + '"></td>' + 
		'</tr><tr>' + 
			'<td><input type="submit" name="submit" class="update" value="' + 
			(existingDoc ? "Update" : "Add") + '"></td>' + 
			'<td><input type="submit" name="cancel" class="cancel" value="Cancel"/></td>' +
		'</tr>' + 
	'</table></form>';
	target.append(html);
	target.children("form#update").data("existingDoc", existingDoc);
}

$(document).ready(function() {
  refreshAddressbook();
  
  $("div#addressbook").click(function(event) {
    var $tgt = $(event.target);
    
    if ($tgt.is('a')) {
      id = $tgt.attr("id");
      if ($tgt.hasClass("edit")){
        if ($tgt.hasClass("edit")) {
        	$("button#add").show();
        	$("form#update").remove();
        	$db.openDoc(id, { success: function(doc) {
        		addUpdateForm($tgt.parent(), doc);
        	}});
        }
      }
      
      if ($tgt.hasClass("delete")){
        html = '&nbsp;<span class="deleteconfirm">Sure? <a bitly="BITLY_PROCESSED" href="#" id="' + id + '" class="dodelete">Yes</a> <a bitly="BITLY_PROCESSED" href="#" class="canceldelete">No</a></span>';
        $tgt.parent().append(html);
      }
      
      if ($tgt.hasClass("dodelete")){
        $db.openDoc(id, { success: function(doc) {
          $db.removeDoc(doc, { success: function(){
            $tgt.parents("div.address").remove();
          }})
        }});
      }
      
      if ($tgt.hasClass("canceldelete")) {
        $tgt.parents("span.deleteconfirm").remove();
      }
    }
  });
  
  $("button#add").click(function(event) {
  	$("form#update").remove();
  	$("button#add").hide();
  	addUpdateForm($("div#add"));
  });
  $("input.cancel").live('click', function(event) {
  	$("button#add").show();
  	$("form#update").remove();
  	return false;
  });
  $("input.update").live('click', function(event) {
  	var $tgt = $(event.target);
  	var $form = $tgt.parents("form#update");
  	var $doc = $form.data('existingDoc') || {};
  	$doc.type = "address";
  	$doc.name = $form.find("input#name").val();
  	$doc.mobile = $form.find("input#mobile").val();
  	$db.saveDoc(
  		$doc, { success: function(){
  			$("button#add").show();
  			$("form#update").remove();
  			refreshAddressbook();
  		}
  	});
  	return false;
  })
});

