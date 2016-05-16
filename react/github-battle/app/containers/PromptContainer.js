var React = require('react');
var transparentBg = require('../styles').transparentBg;

var PromptContainer = React.createClass({
  contextTypes: {
    router: React.PropTypes.object.isRequired
  },
  getInitialState: function() {
    return {
      username: ''
    }
  },
  onUpdateUser: function(e) {
    this.setState({
      username: e.target.value
    })
  },
  onSubmitUser: function(e) {
    e.preventDefault;
    var username = this.state.username;
    this.setState({
      username: ''
    });

    console.log(this.props);

    if (this.props.routeParams.playerOne) {
      this.context.router.push({
        pathname: '/battle',
        query: {
          playerOne: this.props.routeParams.playerOne,
          playerTwo: this.state.username
        }
      })
    } else {
      this.context.router.push('/playerTwo/' + this.state.username);
    }
  },
  render: function() {
    return (
      <div className="jumbotron text-center" style={transparentBg}>
        <h1>{this.props.route.header}</h1>
        <div className="col-sm-12">
          <form onSubmit={this.onSubmitUser}>
            <div className="form-group">
              <input
                className="form-control"
                placeholder="Github username"
                onChange={this.onUpdateUser}
                value={this.state.username}
                type="text"/>
            </div>
            <div className="form-group">
              <button
                className="btn btn-success"
                type="submit">
                  Continue
              </button>
            </div>
          </form>
        </div>
      </div>
    )
  }
})

module.exports = PromptContainer;
