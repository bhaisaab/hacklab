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
    var Booking = Backbone.Model.extend({
    });

    var BookingCollection = Backbone.Collection.extend({
        model: Booking,
        url: '/search'
    });

    //Views
    var ResultListView = Backbone.View.extend({
       tagName: "ul",

       initialize: function(){
            this.model.bind("reset", this.render, this);
       },

       render: function(eventName){
           _.each(this.model.models, function(booking){
               $(this.el).append(new ResultListItemView({model: booking}).render().el)
           }, this);
           $(this.el).html(this.template(this.model.toJSON()));
           return this;
       }
    });

    var ResultListItemView = Backbone.View.extend({
       tagName: "li",
       template: _.template($("#result_list_item")),
       render: function(eventName){
           $(this.el).html(this.template(this.model.toJSON()));
           return this;
       }
    });

    var ResultView = Backbone.View.extend({
        el: $("#content_holder"),
        template: $("#result_template").html(),

        initialize: function(){
            this.render();  
        },

        render: function(){
            var tmpl = _.template(this.template);
            $(this.el).html(tmpl);
            //$(this.el).append(this.template(this.model.get('name'))));

 //           var resultHolder = $("#result_holder");
   //         this.model.each( function(model){ resultHolder.append("<p>" + model.get('name') + "</p>")});

            return this;
        }
    });

    var SearchView = Backbone.View.extend({
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
            app.navigate("search", true);
            return false;
            var bookingResults = new BookingCollection();

            bookingResults.fetch({data: {emails: $("#emails").val(), date: $("#date").val(), start_time: $("#start_time").val(), duration: $("#duration").val(), city: $("#city").val()}});
 
            var result = new ResultView({model: bookingResults});

        }
    });

    //Router
    var AppRouter = Backbone.Router.extend({
        routes: {
            "search": "search", //#search
          //  "*actions": "defaultRoute" // matches http://example.com/#anything-here
        },
        initialize:function () {
            this.searchView = new SearchView();
            $('#content_holder').html(new SearchView().render().el);
        },
        defaultRoute: function( actions ){
            // The variable passed in matches the variable in the route definition "actions"
        },
        search: function(){
            //create instance of master view
            var bookingList = new BookingCollection();
            var bookingListView = new ResultListView({model: this.bookingList});
            bookingList.fetch({data: {emails: $("#emails").val(), date: $("#date").val(), start_time: $("#start_time").val(), duration: $("#duration").val(), city: $("#city").val()}});
            $("#content_holder").html(this.bookingListView.render().el);
        }
    });

    // Initiate the router
    var app = new AppRouter;

    // Start Backbone history a neccesary step for bookmarkable URL's
    Backbone.history.start();

} (jQuery));


