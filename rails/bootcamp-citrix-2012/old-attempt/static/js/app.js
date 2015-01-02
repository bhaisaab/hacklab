$(document).ready(function() {
    $('#date').datepicker();

    $('#date').bind('change', function() {
      var selectedDate = $(this).val();
      var prettyDate = new Date(selectedDate).format('fullDate');
      $('#date-text').html(prettyDate);
    });
  });

(function ($) {

//Models
window.Booking = Backbone.Model.extend({
defaults: {
      text: 'hello',
      grade: 'world'
    }
});

window.BookingCollection = Backbone.Collection.extend({
    model: Booking,
    url: '/search'
});

// Views

window.ResultView = Backbone.View.extend({
    el: $("#content_holder"),
    template: $("#result_template").html(),

    initialize: function(){
        this.collection = new window.BookingCollection();
        this.collection.bind("reset", this.render, this);
        this.collection.bind("change", this.render, this);
        this.collection.fetch();//{data: {emails: $("#emails").val(), date: $("#date").val(), start_time: $("#start_time").val(), duration: $("#duration").val(), city: $("#city").val()}}
        alert("here in view" );
        //this.render();
    },

    render: function(){
        console.log(this.collection.toJSON());
        var tmpl = _.template(this.template);
        $(this.el).html(tmpl({bookings: this.collection.toJSON()}));
        return this;
    },

    events: {
        "click button[id=search_button]": "doSearch"
    },

    doSearch: function(event){
        app.navigate("book", true);
        return false;
    }
});

window.SearchView = Backbone.View.extend({
    el: $("#content_holder"),
    template: $("#search_template").html(),

    initialize: function(){
        this.render();
    },

    render: function(){
        var tmpl = _.template(this.template);
        $(this.el).html(tmpl);
        return this;
    },

    events: {
        "click button[id=search_button]": "doSearch"
    },

    doSearch: function(event){
        app.navigate("book", true);
        return false;
    }
});

//Views
window.BookingListView = Backbone.View.extend({

    tagName:'ul',

    initialize:function () {
        //this.model.bind("reset", this.render, this);
        this.render();
    },

    render:function (eventName) {
        _.each(this.model.models, function (booking) {
            $(this.el).append(new BookingListItemView({model:booking}).render().el);
        }, this);
        return this;
    }

});

window.BookingListItemView = Backbone.View.extend({

    tagName:"li",

    template:_.template($('#result_list_item').html()),

    render:function (eventName) {
            alert("yo"+ model.toJSON());
        $(this.el).html(this.template(this.model.toJSON()));
        return this;
    }

});

window.BookingView = Backbone.View.extend({

    template:_.template($('#result_template').html()),

    render:function (eventName) {
        $(this.el).html(this.template(this.model.toJSON()));
        return this;
    }

});

// Router
var AppRouter = Backbone.Router.extend({

    routes: {
        "book": "searchRooms"
    },

    initialize: function () {
        this.searchView = new SearchView();
        //$('#content_holder').html(new SearchView().render().el);
    },

    searchRooms: function () {

        //var bookingResults = new BookingCollection();
        //bookingResults.fetch({data: {emails: $("#emails").val(), date: $("#date").val(), start_time: $("#start_time").val(), duration: $("#duration").val(), city: $("#city").val()}});
        var result = new window.ResultView();

        //this.bookingList = new window.BookingCollection();
        //this.bookingListView = new window.BookingListView({model:this.bookingList});
        //var p = this.bookingList.fetch({data: {emails: $("#emails").val(), date: $("#date").val(), start_time: $("#start_time").val(), duration: $("#duration").val(), city: $("#city").val()}, processData:true});

        //console.log(JSON.parse(p))

       // $('#content_holder').html(this.bookingListView.render().el);
    },

    searchRooms22: function (id) {
        //this.wine = this.bookingList.get(id);
        //this.wineView = new BookingView({model:this.wine});
        //$('#content_holder').html(this.bookingView.render().el);

        //create instance of master view
        //var bookingList = new BookingCollection();
       // var bookingListView = new ResultListView({model: this.bookingList});
        //bookingList.fetch({data: {emails: $("#emails").val(), date: $("#date").val(), start_time: $("#start_time").val(), duration: $("#duration").val(), city: $("#city").val()}});
        //$("#content_holder").html(this.bookingListView.render().el);

    }
});

var app = new AppRouter();
Backbone.history.start();
} (jQuery));

